#include "structs.h"

#define SHAPE_AS_PLANE(shape) ((t_plane *)(shape)->object)


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

void test_plane()
{
    // The normal of a plane is constant everywhere
    t_plane pl = plane();
    t_tuple n1 = local_normal_at_plane(&pl.base, point(0, 0, 0));
    t_tuple n2 = local_normal_at_plane(&pl.base, point(10, 0, -10));
    t_tuple n3 = local_normal_at_plane(&pl.base, point(-5, 0, 150));
    assert(n1.x == 0 && n1.y == 1 && n1.z == 0);
    assert(n2.x == 0 && n2.y == 1 && n2.z == 0);
    assert(n3.x == 0 && n3.y == 1 && n3.z == 0);
    printf("PASSED: The normal of a plane is constant everywhere\n");

    // Intersect with a ray parallel to the plane
    t_ray r = ray(point(0, 10, 0), vector(0, 0, 1));
    t_intersections xs = local_intersect_plane(&pl.base, r);
    assert(xs.count == 0);
    printf("PASSED: Intersect with a ray parallel to the plane\n");

    // Intersect with a ray coplanar to the plane
    r = ray(point(0, 0, 0), vector(0, 0, 1));
    xs = local_intersect_plane(&pl.base, r);
    assert(xs.count == 0);
    printf("PASSED: Intersect with a ray coplanar to the plane\n");

    // Ray intersecting a plane from above
    t_plane pl1 = plane();
    t_ray r1 = ray(point(0, 10, 0), vector(0, -1, 0));
    t_intersections xs1 = local_intersect_plane(&pl1.base, r1);
    assert(xs1.count == 1);
    assert(xs1.array[0].t == 10);
    assert(xs1.array[0].object == &pl1);
    printf("PASSED: Ray intersecting a plane from above\n");

    // Ray intersecting a plane from below
    t_ray r2 = ray(point(0, -1, 0), vector(0, 1, 0));
    t_intersections xs2 = local_intersect_plane(&pl1.base, r2);
    assert(xs2.count == 1);
    assert(xs2.array[0].t == 1);
    assert(xs2.array[0].object == &pl1);
    printf("PASSED: Ray intersecting a plane from below\n");


}

