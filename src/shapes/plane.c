#include "structs.h"

t_shape	*plane(t_tuple point_pl, t_tuple normal)
{
	t_shape	*object;
	t_plane	*pl;

	pl = calloc(1, sizeof(t_plane));
	if (!pl)
		return (NULL);
	point_pl = point(0, 0, 0);
	normal = vector(0, 1, 0);
	pl->point = point_pl;
	pl->normal = normal;
	object = shape();
	object->object = &pl;
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


