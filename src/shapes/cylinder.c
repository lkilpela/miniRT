#include "structs.h"

t_shape	*cylinder(t_tuple center, t_tuple axis, double radius, double height)
{
	t_shape		*object;
	t_cylinder	*cy;
	
	cy = calloc(1, sizeof(t_cylinder));
	if (!cy)
		return (NULL);
	cy->center = center;
	cy->axis = axis;
	cy->radius = radius;
	cy->height = height;
	object = shape();
	cy->minimum = -INFINITY;
	cy->maximum = INFINITY;
	cy->closed = false;
	object->local_intersect = local_intersect_cylinder;
	object->local_normal_at = local_normal_at_cylinder;
	return (object);
}

void set_cylinder_params(t_shape *shape, t_tuple center, t_tuple axis,
					double radius, double height)
{
	t_cylinder	*cy;
	t_matrix	*translation_matrix;
	t_matrix	*scaling_matrix;
	t_matrix	*rotation_matrix;

	if (shape->id == CYLINDER)
	{
		cy = (t_cylinder *)(shape)->object;
		// Set the minimum and maximum y-values for truncation
		cy->minimum = -height / 2;
		cy->maximum = height / 2;
		cy->closed = true;
		// Prepare transformation matrices
		translation_matrix = translation(center.x, center.y, center.z);
		scaling_matrix = scaling(radius, height, radius);
		rotation_matrix = combine_rotations(axis.x, axis.y, axis.z);
		// Apply the combined transformation
		chaining_transformations(shape, translation_matrix,
							scaling_matrix, rotation_matrix);
	}
}

t_intersections local_intersect_cylinder(t_shape *shape, t_ray r)
{
    t_cylinder		*cy;
	t_intersections	result;
	float			a;
	
	cy = (t_cylinder *)(shape)->object;
    result.count = 0;
    result.array = NULL;
	a = r.direction.x * r.direction.x + r.direction.z * r.direction.z;
    if (a < EPSILON && a > -EPSILON)
    {
        // Ray is parallel to the y-axis
        intersect_caps(shape, r, result);
        return (result);
    }

    float b = 2 * r.origin.x * r.direction.x + 2 * r.origin.z * r.direction.z;
    float c1 = r.origin.x * r.origin.x + r.origin.z * r.origin.z - 1;
    float discriminant = b * b - 4 * a * c1;

    if (discriminant < 0)
    {
        // Ray does not intersect the cylinder
        intersect_caps(shape, r, result);
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
    intersect_caps(shape, r, result);
    return (result);
}

void free_intersections(t_intersections *intersections)
{
    free(intersections->array);
}

void	intersect_caps(t_shape *shape, t_ray r, t_intersections result)
{
	t_cylinder		*cy;
	float			t;
	t_intersection	i;
	t_intersections xs;

	cy = (t_cylinder *)(shape)->object;
	if (!cy->closed || fabs(r.direction.y) < EPSILON)
		return ;
	t = (cy->minimum - r.origin.y) / r.direction.y;
	if (check_cap(r, t))
	{
		i = intersection(t, shape);
		result = intersections_array(1, &i);
	}
	t = (cy->maximum - r.origin.y) / r.direction.y;
	if (check_cap(r, t))
	{
		i = intersection(t, shape);
		xs = intersections_array(1, &i);
		add_intersections(result, xs);
		free_intersections(&xs);
	}
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

