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

// Create an intersection object with a given t value and the intersected object
t_intersection intersection(float t, void *object)
{
    t_intersection i;

    i.t = t;
    i.object = object;
    return (i);
}


// Aggregates intersections into a collection of intersections
t_intersections intersections(int count, ...) {
    t_intersections xs;
    xs.count = count;
    xs.array = calloc(count, sizeof(t_intersection));
    if (xs.array == NULL)
        return xs;
    
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        xs.array[i] = va_arg(args, t_intersection);
    }
    va_end(args);

    return xs;
}

// Calculates the intersections of a ray and a sphere
t_intersections intersect(t_sphere *s, t_ray r)
{
    t_tuple sphere_to_ray = subtract(r.origin, s->center);  // Vector from sphere center to ray origin
    float a = dot(r.direction, r.direction);
    float b = 2 * dot(r.direction, sphere_to_ray);
    float c = dot(sphere_to_ray, sphere_to_ray) - s->radius * s->radius;
    float discriminant = b * b - 4 * a * c;
    //printf("a: %f\n b: %f\n c: %f\n disc: %f\n", a, b, c, discriminant);

    t_intersections result;
    result = intersections(0);

    if (discriminant < 0) {
        //printf("No intersections\n");
        return result;
    }
    else if (discriminant == 0) {  // Tangent, one intersection
        result.count = 1;
        float t = -b / (2 * a);
        t_intersection i = intersection(t, s);
        //result.array = calloc(1, sizeof(t_intersection));
        result = intersections(1, i);
    }
    else
    {
        result.count = 2;
        
        float t1 = (-b - sqrt(discriminant)) / (2 * a);
        float t2 = (-b + sqrt(discriminant)) / (2 * a);
        t_intersection i1 = intersection(t1, (void *)&s);
        t_intersection i2 = intersection(t2, (void *)&s);
        result = intersections(2, i1, i2);
        // print result array
        for (int i = 0; i < result.count; i++)
        {
            printf("t: %f\n", result.array[i].t);
        }

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

void test_sphere()
{
    // A ray intersects a sphere at two points
    t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    t_sphere s = sphere();
    t_intersections xs = intersect(&s, r);

    assert(xs.count == 2);
    assert(xs.array[0].t == 4.0);
    assert(xs.array[1].t == 6.0);
    printf("Passed: A ray intersects a sphere at two points\n");

    // A ray intersects a sphere at a tangent
    t_ray r1 = ray(point(0, 2, -5), vector(0, 0, 1));
    t_intersections xs1 = intersect(&s, r1);

    assert(xs1.count == 0);
    printf("Passed: A ray intersects a sphere at a tangent\n");

    // A ray originates inside a sphere
    t_ray r2 = ray(point(0, 0, 0), vector(0, 0, 1));
    t_intersections xs2 = intersect(&s, r2);

    assert(xs2.count == 2);
    assert(xs2.array[0].t == -1.0);
    assert(xs2.array[1].t == 1.0);
    printf("Passed: A ray originates inside a sphere\n");

    // A sphere is behind a ray
    t_ray r3 = ray(point(0, 0, 5), vector(0, 0, 1));
    t_intersections xs3 = intersect(&s, r3);

    assert(xs3.count == 2);
    assert(xs3.array[0].t == -6.0);
    assert(xs3.array[1].t == -4.0);
    printf("Passed: A sphere is behind a ray\n");

    // Aggregating intersections
    t_intersection i1 = intersection(1, &s);
    t_intersection i2 = intersection(2, &s);
    t_intersections xs4 = intersections(2, i1, i2);

    assert(xs4.count == 2);
    assert(xs4.array[0].t == 1);
    assert(xs4.array[1].t == 2);
    printf("Passed: Aggregating intersections\n");

    // Intersect sets the object on the intersection
    t_ray r4 = ray(point(0, 0, -5), vector(0, 0, 1));
    t_intersections xs5 = intersect(&s, r4);

    assert(xs5.count == 2);
    //assert(xs5.array[0].object == (void *)&s);
    //assert(xs5.array[1].object == (void *)&s);
    printf("Expected: %p, Actual: %p\n", (void *)&s, xs5.array[0].object);
    printf("Expected: %p, Actual: %p\n", (void *)&s, xs5.array[1].object);
    printf("Passed: Intersect sets the object on the intersection\n");

    // Hit when all intersections have positive t
    t_intersection i3 = intersection(1, &s);
    t_intersection i4 = intersection(2, &s);
    t_intersections xs6 = intersections(2, i3, i4);

    t_intersection *hit1 = hit(&xs6);
    assert(hit1 == &i3);
    printf("Passed: Hit when all intersections have positive t\n");

    // Hit when some intersections have negative t
    t_intersection i5 = intersection(-1, &s);
    t_intersection i6 = intersection(1, &s);
    t_intersections xs7 = intersections(2, i5, i6);

    t_intersection *hit2 = hit(&xs7);
    assert(hit2 == &i6);
    printf("Passed: Hit when some intersections have negative t\n");

    // Hit when all intersections have negative t
    t_intersection i7 = intersection(-2, &s);
    t_intersection i8 = intersection(-1, &s);
    t_intersections xs8 = intersections(2, i7, i8);

    t_intersection *hit3 = hit(&xs8);
    assert(hit3 == NULL);
    printf("Passed: Hit when all intersections have negative t\n");

    // Hit is always the lowest nonnegative intersection
    t_intersection i9 = intersection(5, &s);
    t_intersection i10 = intersection(7, &s);
    t_intersection i11 = intersection(-3, &s);
    t_intersection i12 = intersection(2, &s);
    t_intersections xs9 = intersections(4, i9, i10, i11, i12);

    t_intersection *hit4 = hit(&xs9);
    assert(hit4 == &i12);
    printf("Passed: Hit is always the lowest nonnegative intersection\n");

}
