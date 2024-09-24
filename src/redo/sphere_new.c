#include "structs.h"

// Define Type_Safe Casting Macros
#define SHAPE_AS_SPHERE(shape) ((t_sphere *)(shape)->object)

t_sphere_new sphere_new()
{
    t_sphere_new s;

    s.center = point(0, 0, 0);
    s.radius = 1;
    s.base = shape();
    s.base.object = &s;
    s.base.local_intersect = local_intersect_sphere;
    s.base.local_normal_at = local_normal_at_sphere;
    return (s);
}

// Calculates the intersections of a ray and a sphere
t_intersections local_intersect_sphere(t_shape *shape, t_ray r)
{
    t_sphere *s = SHAPE_AS_SPHERE(shape);
    shape->saved_ray = r;

    t_tuple sphere_to_ray = subtract(r.origin, s->center);  // Vector from sphere center to ray origin
    float a = dot(r.direction, r.direction);
    float b = 2 * dot(r.direction, sphere_to_ray);
    float c = dot(sphere_to_ray, sphere_to_ray) - s->radius * s->radius;
    float discriminant = b * b - 4 * a * c;
    //printf("a: %f\n b: %f\n c: %f\n disc: %f\n", a, b, c, discriminant);

    t_intersections result;
    result.count = 0;
    result.array = NULL;

    if (discriminant < 0) {
        //printf("No intersections\n");
        return result;
    }
    else if (discriminant == 0) {  // Tangent, one intersection
        float t = -b / (2 * a);
        t_intersection i = intersection(t, s);
        result = intersections_array(1, &i);
    }
    else
    {
        float t1 = (-b - sqrt(discriminant)) / (2 * a);
        float t2 = (-b + sqrt(discriminant)) / (2 * a);
        t_intersection i1 = intersection(t1, s);
        t_intersection i2 = intersection(t2, s);
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
t_tuple local_normal_at_sphere(t_shape *shape, t_tuple point)
{
    t_sphere *sphere = SHAPE_AS_SPHERE(shape);
    return subtract(point, sphere->center);
}