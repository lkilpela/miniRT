#include "structs.h"

t_shape	*plane(t_tuple p, t_tuple normal)
{
	t_shape	*object;
	t_plane	*pl;
	t_matrix	*translation_matrix;
	t_matrix	*scaling_matrix;
	t_matrix	*rotation_matrix;

	object = shape();
	object->id = PLANE;
	pl = calloc(1, sizeof(t_plane));
	if (!pl)
		return (NULL);
	pl->p = point(0, 0, 0);
	pl->normal = normal; // NEED TO INIT TO VECTOR(0, 1, 0)
	// Prepare transformation matrices
	translation_matrix = translation(p.x, p.y, p.z);
	scaling_matrix = identity_matrix(4);
	rotation_matrix = combine_rotations(0, 0, 0); // NEED TO APPLY CALCULATED ROTATION
	// Apply the combined transformation
	chaining_transformations(object, translation_matrix,
						scaling_matrix, rotation_matrix);
	object->object = pl;
	object->local_intersect = local_intersect_plane;
	object->local_normal_at = local_normal_at_plane;
	return (object);
}

/**
 * @brief Computes the intersections of a ray with a plane.
 *
 * This function determines where a given ray intersects with a plane.
 * If the ray is parallel to the plane (i.e., the y component of the ray's direction is close to zero),
 * no intersection is recorded. Otherwise, the intersection point is calculated and returned.
 *
 * @param shape A pointer to the shape (plane) to intersect with.
 * @param r The ray to test for intersection with the plane.
 * @return A t_intersections structure containing the intersection points.
 */
t_intersections	local_intersect_plane(t_shape *shape, t_ray r)
{
    t_intersections	result;
	float			t;
	t_intersection	i;

    result.count = 0;
    result.array = NULL;
    if (fabs(r.direction.y) < EPSILON)
        return (result);
	t = -r.origin.y / r.direction.y;
    i = intersection(t, shape);
    result = intersections_array(1, &i);
    return (result);
}

/**
 * Computes the local normal vector at a given point on a plane.
 *
 * @param shape A pointer to the shape (plane) for which the normal is being calculated.
 * @param point The point on the plane where the normal is being calculated.
 * @return A t_tuple representing the normal vector at the given point on the plane.
 */
t_tuple	local_normal_at_plane(t_shape *shape, t_tuple point)
{
	(void)point;
	(void)shape;
	return (vector(0, 1, 0));
}


