#include "structs.h"

t_sphere sphere()
{
    t_sphere s;

    s.center = point(0, 0, 0);
    s.radius = 1;
    s.id = 0;
    return (s);
}

t_intersections intersect(t_sphere s, t_ray r)
{
    t_tuple sphere_to_ray = subtract(r.origin, s.center);  // Vector from sphere center to ray origin
    float a = dot(r.direction, r.direction);
    float b = 2 * dot(r.direction, sphere_to_ray);
    float c = dot(sphere_to_ray, sphere_to_ray) - s.radius * s.radius;
    float discriminant = b * b - 4 * a * c;

    t_intersections result;
    result.count = 0;

    if (discriminant >= 0) {
        result.count = 2;
        result.t1 = (-b - sqrt(discriminant)) / (2 * a);
        result.t2 = (-b + sqrt(discriminant)) / (2 * a);
    }
    return result;
}


