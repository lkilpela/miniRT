#include "structs.h"

t_shape	*sphere(t_tuple center, float radius)
{
	t_shape		*object;
	t_sphere	*sp;
	t_matrix	*translation_matrix;
	t_matrix	*scaling_matrix;
	t_matrix	*rotation_matrix;

	object = shape();
	object->id = SPHERE;
	sp = calloc(1, sizeof(t_sphere));
	if (!sp)
		return (NULL);
	sp->center = point(0, 0, 0);
	sp->radius = 1;
	// Prepare transformation matrices
	translation_matrix = translation(center.x, center.y, center.z);
	scaling_matrix = scaling(radius, radius, radius);
	rotation_matrix = combine_rotations(0, 0, 0);
	// Apply the combined transformation
	chaining_transformations(object, translation_matrix,
						scaling_matrix, rotation_matrix);
	object->object = sp;
	object->local_intersect = local_intersect_sphere;
	object->local_normal_at = local_normal_at_sphere;
	return (object);
}

// Calculates the intersections of a ray and a sphere
t_intersections	local_intersect_sphere(t_shape *shape, t_ray r)
{
	t_sphere	*sp;

	sp = (t_sphere *)(shape)->object;

	t_tuple sphere_to_ray = subtract(r.origin, sp->center);  // Vector from sphere center to ray origin
	float a = dot(r.direction, r.direction);
	float b = 2 * dot(r.direction, sphere_to_ray);
	float c = dot(sphere_to_ray, sphere_to_ray) - sp->radius * sp->radius;
	float discriminant = b * b - 4 * a * c;

	t_intersections result;
	result.count = 0;
	result.array = NULL;

	if (discriminant < 0)
		return result;
	else if (discriminant == 0)
	{
		float t = -b / (2 * a);
		t_intersection i = intersection(t, shape);
		result = intersections_array(1, &i);
	}
	else
	{
		float t1 = (-b - sqrt(discriminant)) / (2 * a);
		float t2 = (-b + sqrt(discriminant)) / (2 * a);
		t_intersection i1 = intersection(t1, shape);
		t_intersection i2 = intersection(t2, shape);
		t_intersection array[2] = {i1, i2};
		result = intersections_array(2, array);

	}
	return (result);
}

/**
 * @brief Calculates the normal at a given point on a sphere in local space.
 * 
 * @param shape The shape to calculate the normal for.
 * @param point The point at which to calculate the normal.
 * @return The normal vector at the given point.
 */
t_tuple	local_normal_at_sphere(t_shape *shape, t_tuple point)
{
	t_sphere	*sp;
	t_tuple		normal;

	sp = (t_sphere *)(shape)->object;	
	normal = subtract(point, sp->center);
	return (normal);
}
