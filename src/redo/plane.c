#include "structs.h"

#define SHAPE_AS_PLANE(shape) ((t_plane *)(shape)->object)

typedef struct s_plane
{
    t_shape base;
}              t_plane;

t_plane plane() 
{
    t_plane pl;

    pl.base = shape();
    pl.base.local_intersect = local_intersect_plane;
    pl.base.local_normal_at = local_normal_at_plane;
    return pl;
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
t_intersections local_intersect_plane(t_shape *shape, t_ray r)
{
    t_plane *pl = SHAPE_AS_PLANE(shape);

    t_intersections result;
    result.count = 0;
    result.array = NULL;

    if (fabs(r.direction.y) < EPSILON)
        return result;

    float t = -r.origin.y / r.direction.y;
    
    t_intersection i = intersection(t, pl);
    result = intersections_array(1, &i);
    return result;
}

/**
 * Computes the local normal vector at a given point on a plane.
 *
 * @param shape A pointer to the shape (plane) for which the normal is being calculated.
 * @param point The point on the plane where the normal is being calculated.
 * @return A t_tuple representing the normal vector at the given point on the plane.
 */
t_tuple local_normal_at_plane(t_shape *shape, t_tuple point)
{
    (void)point;
    (void)shape;
    return vector(0, 1, 0);
}

void set_transform_shape(t_shape *shape, t_matrix *m)
{
    shape->transform = m;
}

void test_plane()
{
    // Ray intersecting a plane from above
    t_plane pl = plane();
    t_ray r = ray(point(0, 10, 0), vector(0, -1, 0));
    t_intersections xs = local_intersect_plane(&pl.base, r);
    assert(xs.count == 1);
    assert(xs.array[0].t == 10);
    assert(xs.array[0].object == &pl);
    free_intersections(&xs);
    printf("PASSED: Ray intersecting a plane from above\n");

    // Ray intersecting a plane from below
    r = ray(point(0, -1, 0), vector(0, 1, 0));
    xs = local_intersect_plane(&pl.base, r);
    assert(xs.count == 1);
    assert(xs.array[0].t == 1);
    assert(xs.array[0].object == &pl);
    free_intersections(&xs);
    printf("PASSED: Ray intersecting a plane from below\n");


}

