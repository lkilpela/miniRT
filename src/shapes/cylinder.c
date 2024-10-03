#include "structs.h"

void	cylinder_transform(t_shape *cy, t_tuple center, t_tuple axis, double radius)
{
	t_matrix	*translation_matrix;
	t_matrix	*scaling_matrix;
	t_matrix	*rotation_matrix;

	rotation_matrix = combine_rotations(calculate_angle(0, axis.x),
			calculate_angle(1, axis.y), calculate_angle(0, axis.z));
	scaling_matrix = scaling(radius, 1, radius);
	translation_matrix = translation(center.x, center.y, center.z);
	chaining_transformations(cy,
						rotation_matrix,
						scaling_matrix,
						translation_matrix);
}

t_shape	*cylinder(t_tuple center, t_tuple axis, double radius, double height)
{
	t_shape		*object;
	t_cylinder	*cy;

	object = shape();
	object->id = CYLINDER;
	cy = calloc(1, sizeof(t_cylinder));
	if (!cy)
		return (NULL);
	cy->minimum = - height / 2;
	cy->maximum = height / 2;
	cylinder_transform(object, center, axis, radius);
	object->object = cy;
	object->local_intersect = local_intersect_cylinder;
	object->local_normal_at = local_normal_at_cylinder;
	return (object);
}

t_coefficients	calculate_coefficients(t_ray r)
{
	t_coefficients coeffs;

	coeffs.a = (r.direction.x * r.direction.x) + (r.direction.z * r.direction.z);
	coeffs.b = 2 * r.origin.x * r.direction.x + 2 * r.origin.z * r.direction.z;
	coeffs.c = r.origin.x * r.origin.x + r.origin.z * r.origin.z - 1;
	return (coeffs);
}

float	calculate_discriminant(t_coefficients coeffs)
{
	float	disc;
	disc = coeffs.b * coeffs.b - 4 * coeffs.a * coeffs.c;
	return (disc);
}

void	find_intersection_points(float disc,
							t_coefficients coeffs, 
							float *t0, float *t1)
{
	*t0 = (-coeffs.b - sqrt(disc)) / (2 * coeffs.a);
	*t1 = (-coeffs.b + sqrt(disc)) / (2 * coeffs.a);
	if (*t0 > *t1)
		ft_swap(t0, t1);
}

bool	is_within_height_bounds(t_cylinder *cy, t_ray r, float t)
{
    float	y;

	y = r.origin.y + t * r.direction.y;
    return ((cy->minimum < y && y < cy->maximum));
}

t_intersections local_intersect_cylinder(t_shape *shape, t_ray r)
{
	t_cylinder		*cy;
	t_intersections	result;
	t_coefficients	coeffs;
	t_intersection	i;
	t_intersections xs;
	float discriminant;
	float t0;
	float t1;

	cy = (t_cylinder *)(shape)->object;
	if (!cy)
		fatal_error("Local_intersect_cylinder: cylinder is NULL\n");
	result.count = 0;
	result.array = NULL;
	coeffs = calculate_coefficients(r);
	if (coeffs.a < EPSILON)
		// Ray is parallel to the y-axis
		return (intersect_caps(shape, r, result));
	discriminant = calculate_discriminant(coeffs);
	if (discriminant < 0)
		// Ray does not intersect the cylinder
		return (intersect_caps(shape, r, result));
	find_intersection_points(discriminant, coeffs, &t0, &t1);
	if (is_within_height_bounds(cy, r, t0))
	{
		i = intersection(t0, shape);
		xs = intersections_array(1, &i);
		result = add_intersections(result, xs);
		free_intersections(&xs);
	}
	if (is_within_height_bounds(cy, r, t1))
	{
		i = intersection(t1, shape);
		xs = intersections_array(1, &i);
		result = add_intersections(result, xs);
		free_intersections(&xs);
	}
	result = intersect_caps(shape, r, result);
	return (result);
}

t_intersections	intersect_caps(t_shape *shape, t_ray r, t_intersections result)
{
	t_cylinder		*cy;
	float			t;
	t_intersection	i;
	t_intersections xs;

	cy = (t_cylinder *)(shape)->object;
	if (fabs(r.direction.y) < EPSILON)
		return (result);
	t = (cy->minimum - r.origin.y) / r.direction.y;
	if (check_cap(r, t))
	{
		i = intersection(t, shape);
		xs = intersections_array(1, &i);
		result = add_intersections(result, xs);
		free_intersections(&xs);
	}
	t = (cy->maximum - r.origin.y) / r.direction.y;
	if (check_cap(r, t))
	{
		i = intersection(t, shape);
		xs = intersections_array(1, &i);
		result = add_intersections(result, xs);
		free_intersections(&xs);
	}
	return (result);
}

/* CYLINDER NORMALS - COMPUTE SQUARE of DISTANCE from Y AXIS
** 1. If the point is at the top of the cylinder
**   - Return (0, 1, 0)
** 2. If the point is at the bottom of the cylinder
**   - Return (0, -1, 0)
** 3. If the point is on the side of the cylinder
**   - Return (x, 0, z)
*/
t_tuple	local_normal_at_cylinder(t_shape *shape, t_tuple point)
{
	t_cylinder	*cy;
	float		dist;

	cy = (t_cylinder *)(shape)->object;
	dist = point.x * point.x + point.z * point.z;
	if (dist < 1 && point.y >= cy->maximum - EPSILON)
		return (vector(0, 1, 0));
	else if (dist < 1 && point.y <= cy->minimum + EPSILON)
		return (vector(0, -1, 0));
	else
		return (vector(point.x, 0, point.z));
}
