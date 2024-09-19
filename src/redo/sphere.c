#include "structs.h"

t_sphere sphere()
{
    t_sphere s;

    s.center = point(0, 0, 0);
    s.radius = 1;
    s.id = 0;
    //s.transform = identify_matrix();
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
t_intersections intersections(int count, ...) {
    t_intersections xs;
    xs.count = count;
    xs.array = calloc(xs.count, sizeof(t_intersection));

    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        xs.array[i] = va_arg(args, t_intersection);
    }
    va_end(args);

    return xs;
}

// Calculates the intersections of a ray and a sphere
t_intersections intersect(t_sphere s, t_ray r)
{
    t_tuple sphere_to_ray = subtract(r.origin, s.center);  // Vector from sphere center to ray origin
    float a = dot(r.direction, r.direction);
    float b = 2 * dot(r.direction, sphere_to_ray);
    float c = dot(sphere_to_ray, sphere_to_ray) - s.radius * s.radius;
    float discriminant = b * b - 4 * a * c;
    printf("a: %f\n b: %f\n c: %f\n disc: %f\n", a, b, c, discriminant);

    t_intersections result;
    result.count = 0;
    result.array = NULL;

    if (discriminant < 0) {
        printf("No intersections\n");
        return result;
    }
    else if (discriminant == 0) {  // Tangent, one intersection
        result.count = 1;
        float t = -b / (2 * a);
        t_intersection i = intersection(t, (void*)&s);
        result.array = calloc(1, sizeof(t_intersection));
        result.array[0] = i;
    }
    else
    {
        result.count = 2;
        
        float t1 = (-b - sqrt(discriminant)) / (2 * a);
        float t2 = (-b + sqrt(discriminant)) / (2 * a);
        t_intersection i1 = intersection(t1, (void *)&s);
        t_intersection i2 = intersection(t2, (void *)&s);
        result = intersections(2, i1, i2);
    }
    return (result);
}

t_intersection *hit(t_intersections *intersections)
{
    t_intersection *hit = NULL;
    for (int i = 0; i < intersections->count; i++)
    {
        if (intersections->array[i].t >= 0)
        {
            if (hit == NULL || intersections->array[i].t < hit->t)
            {
                hit = &intersections->array[i];
            }
        }
    }
    return hit;
}

void test_hit_all_positive()
{
    t_sphere s = sphere();
    t_intersection i1 = intersection(1, &s);
    t_intersection i2 = intersection(2, &s);
    t_intersections xs = intersections(2, i1, i2);

    t_intersection *i = hit(&xs);
    assert(i == &xs.array[0]);
    printf("test_hit_all_positive passed\n");
}

void test_hit_some_negative()
{
    t_sphere s = sphere();
    t_intersection i1 = intersection(-1, &s);
    t_intersection i2 = intersection(1, &s);
    t_intersections xs = intersections(2, i1, i2);

    t_intersection *i = hit(&xs);
    assert(i == &xs.array[1]);
    printf("test_hit_some_negative passed\n");
}

void test_hit_all_negative()
{
    t_sphere s = sphere();
    t_intersection i1 = intersection(-2, &s);
    t_intersection i2 = intersection(-1, &s);
    t_intersections xs = intersections(2, i1, i2);

    t_intersection *i = hit(&xs);
    assert(i == NULL);
    printf("test_hit_all_negative passed\n");
}

void test_hit_lowest_nonnegative()
{
    t_sphere s = sphere();
    t_intersection i1 = intersection(5, &s);
    t_intersection i2 = intersection(7, &s);
    t_intersection i3 = intersection(-3, &s);
    t_intersection i4 = intersection(2, &s);
    t_intersections xs = intersections(4, i1, i2, i3, i4);

    t_intersection *i = hit(&xs);
    assert(i == &xs.array[3]);
    printf("test_hit_lowest_nonnegative passed\n");
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

/*t_intersections *intersections(int count, t_intersection *xs)
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
}*/