#include "structs.h"

void	cylinder_transform(t_shape *cy, t_tuple center, t_tuple axis, double radius, double height)
{
	t_matrix	*translation_matrix;
	t_matrix	*scaling_matrix;
	t_matrix	*rotation_matrix;

	rotation_matrix = combine_rotations(calculate_angle(0, axis.x),
			calculate_angle(0, axis.y), calculate_angle(0, axis.z));
	scaling_matrix = scaling(radius, height, radius);
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

	(void)height;
	object = shape();
	object->id = CYLINDER;
	cy = calloc(1, sizeof(t_cylinder));
	if (!cy)
		return (NULL);
	cy->minimum = - height / 2;
	cy->maximum = height / 2;
	cy->closed = true;

	cylinder_transform(object, center, axis, radius, height);

	object->object = cy;
	object->local_intersect = local_intersect_cylinder;
	object->local_normal_at = local_normal_at_cylinder;
	return (object);
}
// Returns the angle between an axis and the vector 
// from the origin to the point
float	calculate_angle(float a, float b)
{
	float angle;

	angle = atan2(a, b);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

t_intersections local_intersect_cylinder(t_shape *shape, t_ray r)
{
    t_cylinder		*cy;
	t_intersections	result;
	float			a;
	
	cy = (t_cylinder *)(shape)->object;
	if (!cy)
		fatal_error("Local_intersect_cylinder: cylinder is NULL\n");
    result.count = 0;
    result.array = NULL;
	a = r.direction.x * r.direction.x + r.direction.z * r.direction.z;
    if (a < EPSILON && a > -EPSILON)
    {
        // Ray is parallel to the y-axis
        result = intersect_caps(shape, r, result);
        return (result);
    }

    float b = 2 * r.origin.x * r.direction.x + 2 * r.origin.z * r.direction.z;
    float c1 = r.origin.x * r.origin.x + r.origin.z * r.origin.z - 1;
    float discriminant = b * b - 4 * a * c1;

    if (discriminant < 0)
    {
        // Ray does not intersect the cylinder
        result = intersect_caps(shape, r, result);
        return result;
    }

    float t0 = (-b - sqrt(discriminant)) / (2 * a);
    float t1 = (-b + sqrt(discriminant)) / (2 * a);

    if (t0 > t1)
		ft_swap(&t0, &t1);

    float y0 = r.origin.y + t0 * r.direction.y;
    if (cy->minimum < y0 && y0 < cy->maximum)
    {
        t_intersection i0 = intersection(t0, shape);
        result = intersections_array(1, &i0);
    }

    float y1 = r.origin.y + t1 * r.direction.y;
    if (cy->minimum < y1 && y1 < cy->maximum)
    {
        t_intersection i1 = intersection(t1, shape);
        result = intersections_array(1, &i1);
    }
    result = intersect_caps(shape, r, result);
    return (result);
}

void free_intersections(t_intersections *intersections)
{
    free(intersections->array);
}

t_intersections	intersect_caps(t_shape *shape, t_ray r, t_intersections result)
{
	t_cylinder		*cy;
	float			t;
	t_intersection	i;
	t_intersections xs;

	cy = (t_cylinder *)(shape)->object;
	if (!cy)
    {
        ft_printf("Intersect_caps: shape is NULL\n");
        return (result);
    }
	if (!cy->closed || fabs(r.direction.y) < EPSILON)
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

bool	check_cap(t_ray r, float t)
{
	float	x;
	float	z;

	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;
	return (x * x + z * z <= 1);
}

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

