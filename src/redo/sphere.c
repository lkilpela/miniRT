#include "structs.h"

t_sphere sphere()
{
    t_sphere s;

    s.center = point(0, 0, 0);
    s.radius = 1;
    s.id = 0;
    return (s);
}

t_intersections intersect_two_points(t_sphere s, t_ray r)
{
    t_tuple sphere_to_ray = subtract(r.origin, s.center);  // Vector from sphere center to ray origin
    float a = dot(r.direction, r.direction);
    float b = 2 * dot(r.direction, sphere_to_ray);
    float c = dot(sphere_to_ray, sphere_to_ray) - s.radius * s.radius;
    float discriminant = b * b - 4 * a * c;
    printf("a: %f\n b: %f\n c: %f\n disc: %f\n", a, b, c, discriminant);

    t_intersections result;
    result.count = 0;

    if (discriminant < 0) {
        printf("No intersections\n");
    }
    else if (discriminant == 0) {
        result.count = 1;
        result.t1 = -b / (2 * a);
        printf("xs[0]: %f\n", result.t1);
    }
    else if (discriminant >= 0)
    {
        result.count = 2;
        result.t1 = (-b - sqrt(discriminant)) / (2 * a);
        printf("xs[0]: %f\n", result.t1);
        result.t2 = (-b + sqrt(discriminant)) / (2 * a);
        printf("xs[1]: %f\n", result.t2);
    }
    return result;
}

/*void test_sphere_intersects_2p()
{
    t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    t_sphere s = sphere();
    t_intersections xs = intersect_two_points(s, r);

    assert(xs.count == 2);
    assert(xs.t1 == 4.0);
    assert(xs.t2 == 6.0);
    printf("test_sphere_intersects_ray passed\n");
}

void test_sphere_intersects_tangent()
{
    t_ray r = ray(point(0, 1, -5), vector(0, 0, 1));
    t_sphere s = sphere();
    t_intersections xs = intersect_two_points(s, r);

    assert(xs.count == 2);
    assert(xs.t1 == 5.0);
    assert(xs.t2 == 5.0);
    printf("test_sphere_intersects_ray passed\n");
}

void test_sphere_intersects_raymiss()
{
    t_ray r = ray(point(0, 2, -5), vector(0, 0, 1));
    t_sphere s = sphere();
    t_intersections xs = intersect_two_points(s, r);

    assert(xs.count == 0);
    //printf("test_sphere_intersects_ray passed\n");
}

void test_sphere_intersects_rayinside()
{
    t_ray r = ray(point(0, 0, 0), vector(0, 0, 1));
    t_sphere s = sphere();
    t_intersections xs = intersect_two_points(s, r);

    assert(xs.count == 2);
    assert(xs.t1 == -1.0);
    assert(xs.t2 == 1.0);
    printf("test_sphere_intersects_ray passed\n");
}

void test_sphere_behind_ray()
{
    t_ray r = ray(point(0, 0, 5), vector(0, 0, 1));
    t_sphere s = sphere();
    t_intersections xs = intersect_two_points(s, r);

    assert(xs.count == 2);
    assert(xs.t1 == -6.0);
    assert(xs.t2 == -4.0);
    printf("test_sphere_intersects_ray passed\n");
}*/