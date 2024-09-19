#include "structs.h"

t_sphere sphere()
{
    t_sphere s;

    s.center = point(0, 0, 0);
    s.radius = 1;
    s.id = 0;
    return (s);
}

// Creates an intersection
t_intersection intersection(float t, void *object)
{
    t_intersection i;

    i.t = t;
    i.object = object;
    return (i);
}

// Aggregates intersections into a list of intersections
t_intersections *intersections(int count, t_intersection *xs)
{
    t_intersections *intersections;
    int i;

    i = 0;
    intersections = calloc(1, sizeof(t_intersections));
    intersections->count = count;
    intersections->array = calloc(count, sizeof(t_intersection));
    while (i < count)
    {
        intersections->array[i] = xs[i];
        printf("array[%d]: %f\n", i, xs[i].t);
        i++;
    }

    return (intersections);
}

// Calculates the intersections of a ray and a sphere
t_intersections *intersect(t_sphere s, t_ray r)
{
    t_tuple sphere_to_ray = subtract(r.origin, s.center);  // Vector from sphere center to ray origin
    float a = dot(r.direction, r.direction);
    float b = 2 * dot(r.direction, sphere_to_ray);
    float c = dot(sphere_to_ray, sphere_to_ray) - s.radius * s.radius;
    float discriminant = b * b - 4 * a * c;
    printf("a: %f\n b: %f\n c: %f\n disc: %f\n", a, b, c, discriminant);

    t_intersections *result = intersections(2, calloc(2, sizeof(t_intersection)));
    result->count = 0;
    result->array = NULL;

    if (discriminant < 0) {
        printf("No intersections\n");
        return result;
    }
    else
    {
        result->count = 2;
        result->array[0] = intersection((-b - sqrt(discriminant)) / (2 * a), &s);
        result->array[1] = intersection((-b + sqrt(discriminant)) / (2 * a), &s);
    }
    return (result);
}



/*void test_sphere_intersects_2p()
{
    t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    t_sphere s = sphere();
    t_intersections *xs = intersect(s, r);

    assert(xs->count == 2);
    assert(xs->xs[0].object == (void *)&s);
    assert(xs->xs[1].object == (void *)&s);
    printf("test_sphere_intersects_ray passed\n");
}*/

/*void test_aggregating_intersections()
{
    t_sphere s = sphere();
    t_intersection i1 = intersection(1, &s);
    t_intersection i2 = intersection(2, &s);
    t_intersection xs[] = {i1, i2};
    t_intersections *result = intersections(2, xs);

    assert(result->count == 2);
    assert(result->xs[0].t == 1);
    assert(result->xs[1].t == 2);
    free(result);
    printf("test_aggregating_intersections passed\n");
}*/


/*
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