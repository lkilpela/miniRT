#include "structs.h"

t_sphere sphere()
{
    t_sphere s;

    s.center = point(0, 0, 0);
    s.radius = 1;
    s.id = 0;
    s.transform = identity_matrix(4);
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
t_intersections intersections_array(int count, t_intersection *array)
{
    t_intersections xs;
    xs.count = count;
    xs.array = calloc(count, sizeof(t_intersection));
    if (xs.array == NULL)
        return xs;

    for (int i = 0; i < count; i++)
        xs.array[i] = array[i];

    return xs;
}

// Calculates the intersections of a ray and a sphere
t_intersections intersect(t_sphere *s, t_ray *r)
{
    t_tuple sphere_to_ray = subtract(r->origin, s->center);  // Vector from sphere center to ray origin
    float a = dot(r->direction, r->direction);
    float b = 2 * dot(r->direction, sphere_to_ray);
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

// Calculates the intersections of a ray and a sphere
t_intersections intersect_transformation(t_sphere *s, t_ray *r)
{
    t_matrix *inv = inverse(s->transform);
    t_ray transfromed_ray = transform(*r, inv);
    t_tuple sphere_to_ray = subtract(transfromed_ray.origin, s->center);  // Vector from sphere center to ray origin
    float a = dot(transfromed_ray.direction, transfromed_ray.direction);
    float b = 2 * dot(transfromed_ray.direction, sphere_to_ray);
    float c = dot(sphere_to_ray, sphere_to_ray) - s->radius * s->radius;
    float discriminant = b * b - 4 * a * c;
    //printf("a: %f\n b: %f\n c: %f\n disc: %f\n", a, b, c, discriminant);

    t_intersections result;
    result = intersections_array(0, NULL);

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


/* HIT 
** Loop through all intersections and return the intersection with the lowest positive t value
** If there are no positive t values, return NULL
*/
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

void set_transform(t_sphere *s, t_matrix *m)
{
    s->transform = m;
}

/* NORMAL AT
** Calculate the normal vector on a sphere at a given point
** The normal vector is the vector from the center of the sphere to the point
** Normalize the vector to get a unit vector
*/
t_tuple normal_at(t_sphere *s, t_tuple world_point)
{
    t_tuple object_point = matrix_multiply_tuple(inverse(s->transform), world_point);
    t_tuple object_normal = subtract(object_point, s->center);
    t_tuple world_normal = matrix_multiply_tuple(transpose(inverse(s->transform)), object_normal);
    world_normal.w = 0;
    return (normalize(world_normal));
}


void test_sphere()
{
    // A ray intersects a sphere at two points
    t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    t_sphere s = sphere();
    t_intersections xs = intersect(&s, &r);

    assert(xs.count == 2);
    assert(xs.array[0].t == 4.0);
    assert(xs.array[1].t == 6.0);
    printf("Passed: A ray intersects a sphere at two points\n");

    // A ray intersects a sphere at a tangent
    t_ray r1 = ray(point(0, 2, -5), vector(0, 0, 1));
    t_intersections xs1 = intersect(&s, &r1);

    assert(xs1.count == 0);
    printf("Passed: A ray intersects a sphere at a tangent\n");

    // A ray originates inside a sphere
    t_ray r2 = ray(point(0, 0, 0), vector(0, 0, 1));
    t_intersections xs2 = intersect(&s, &r2);

    assert(xs2.count == 2);
    assert(xs2.array[0].t == -1.0);
    assert(xs2.array[1].t == 1.0);
    printf("Passed: A ray originates inside a sphere\n");

    // A sphere is behind a ray
    t_ray r3 = ray(point(0, 0, 5), vector(0, 0, 1));
    t_intersections xs3 = intersect(&s, &r3);

    assert(xs3.count == 2);
    assert(xs3.array[0].t == -6.0);
    assert(xs3.array[1].t == -4.0);
    printf("Passed: A sphere is behind a ray\n");

    // Aggregating intersections
    t_intersection i1 = intersection(1, &s);
    t_intersection i2 = intersection(2, &s);
    t_intersections xs4 = intersections_array(2, (t_intersection[]){i1, i2});

    assert(xs4.count == 2);
    assert(xs4.array[0].t == 1);
    assert(xs4.array[1].t == 2);
    printf("Passed: Aggregating intersections\n");

    // Intersect sets the object on the intersection
    t_ray r4 = ray(point(0, 0, -5), vector(0, 0, 1));
    t_intersections xs5 = intersect(&s, &r4);

    assert(xs5.count == 2);
    assert(xs5.array[0].object == (void *)&s);
    assert(xs5.array[1].object == (void *)&s);
    //printf("Expected: %p, Actual: %p\n", (void *)&s, xs5.array[0].object);
    //printf("Expected: %p, Actual: %p\n", (void *)&s, xs5.array[1].object);
    printf("Passed: Intersect sets the object on the intersection\n");

    // Hit when all intersections have positive t
    t_intersection i3 = intersection(1, &s);
    t_intersection i4 = intersection(2, &s);
    t_intersections xs6 = intersections_array(2, (t_intersection[]){i3, i4});
    //printf("i3.t: %f\n i3.object: %p\n", i3.t, i3.object);
   // printf("i4.t: %f\n i4.object: %p\n", i4.t, i4.object);
    t_intersection *hit1 = hit(&xs6);
   // printf("hit1.t: %f\n hit1.object: %p\n", hit1->t, hit1->object);

    assert(hit1->t == i3.t);
    assert(hit1->object == i3.object);
    printf("Passed: Hit when all intersections have positive t\n");

    // Hit when some intersections have negative t
    t_intersection i5 = intersection(-1, &s);
    t_intersection i6 = intersection(1, &s);
    t_intersections xs7 = intersections_array(2, (t_intersection[]){i5, i6});

    t_intersection *hit2 = hit(&xs7);
    assert(hit2->t == i6.t);
    assert(hit2->object == i6.object);
    printf("Passed: Hit when some intersections have negative t\n");

    // Hit when all intersections have negative t
    t_intersection i7 = intersection(-2, &s);
    t_intersection i8 = intersection(-1, &s);
    t_intersections xs8 = intersections_array(2, (t_intersection[]){i7, i8});

    t_intersection *hit3 = hit(&xs8);
    assert(hit3 == NULL);
    printf("Passed: Hit when all intersections have negative t\n");

    // Hit is always the lowest nonnegative intersection
    t_intersection i9 = intersection(5, &s);
    t_intersection i10 = intersection(7, &s);
    t_intersection i11 = intersection(-3, &s);
    t_intersection i12 = intersection(2, &s);
    t_intersections xs9 = intersections_array(4, (t_intersection[]){i9, i10, i11, i12});

    t_intersection *hit4 = hit(&xs9);
    assert(hit4->t == i12.t);
    assert(hit4->object == i12.object);
    printf("Passed: Hit is always the lowest nonnegative intersection\n");

}

void test_sphere_transformation()
{
    // A sphere has a default transformation
    t_sphere s = sphere();
    assert(matrices_are_equal(s.transform, identity_matrix(4)));
    printf("Passed: A sphere has a default transformation\n");

    // Changing a sphere's transformation
    t_matrix *t = translation(2, 3, 4);
    set_transform(&s, t);
    assert(matrices_are_equal(s.transform, t));
    printf("Passed: Changing a sphere's transformation\n");

    // Intersecting a scaled sphere with a ray
    t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    t_sphere s1 = sphere();
    printf("Before scaling\n");
    print_matrix(s1.transform);
    set_transform(&s1, scaling(2, 2, 2));
    printf("After scaling\n");
    print_matrix(s1.transform);
    t_intersections xs = intersect_transformation(&s1, &r);
    assert(xs.count == 2);
    assert(xs.array[0].t == 3);
    assert(xs.array[1].t == 7);
    printf("Passed: Intersecting a scaled sphere with a ray\n");

    // Intersecting a translated sphere with a ray
    t_ray r1 = ray(point(0, 0, -5), vector(0, 0, 1));
    t_sphere s2 = sphere();
    printf("Before translation\n");
    print_matrix(s2.transform);
    set_transform(&s2, translation(5, 0, 0));
    printf("After translation\n");
    print_matrix(s2.transform);
    t_intersections xs1 = intersect_transformation(&s2, &r1);
    printf("xs1.array[0].t: %f\n", xs1.array[0].t);
    assert(xs1.count == 0);
    printf("Passed: Intersecting a translated sphere with a ray\n");

}

void test_normal_at()
{
    // The normal on a sphere at a point on the x-axis
    t_sphere s = sphere();
    t_tuple n = normal_at(&s, point(1, 0, 0));
    t_tuple expected = vector(1, 0, 0);
    assert(equal_tuples(n, expected, EPSILON));
    printf("Passed: The normal on a sphere at a point on the x-axis\n");

    // The normal on a sphere at a point on the y-axis
    t_sphere s1 = sphere();
    t_tuple n1 = normal_at(&s1, point(0, 1, 0));
    t_tuple expected1 = vector(0, 1, 0);
    assert(equal_tuples(n1, expected1, EPSILON));
    printf("Passed: The normal on a sphere at a point on the y-axis\n");

    // The normal on a sphere at a point on the z-axis
    t_sphere s2 = sphere();
    t_tuple n2 = normal_at(&s2, point(0, 0, 1));
    t_tuple expected2 = vector(0, 0, 1);
    assert(equal_tuples(n2, expected2, EPSILON));
    printf("Passed: The normal on a sphere at a point on the z-axis\n");

    // The normal on a sphere at a nonaxial point
    t_sphere s3 = sphere();
    t_tuple n3 = normal_at(&s3, point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
    t_tuple expected3 = vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3);
    assert(equal_tuples(n3, expected3, EPSILON));
    printf("Passed: The normal on a sphere at a nonaxial point\n");

    // The normal is a normalized vector
    t_sphere s4 = sphere();
    t_tuple n4 = normal_at(&s4, point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
    assert(equal_tuples(n4, normalize(n4), EPSILON));
    printf("Passed: The normal is a normalized vector\n");

    // Computing the normal on a translated sphere
    t_sphere s5 = sphere();
    set_transform(&s5, translation(0, 1, 0));
    t_tuple n5 = normal_at(&s5, point(0, 1.70711, -0.70711));
    t_tuple expected5 = vector(0, 0.70711, -0.70711);
    assert(equal_tuples(n5, expected5, EPSILON));
    printf("Passed: Computing the normal on a translated sphere\n");

    // Computing the normal on a transformed sphere
    t_sphere s6 = sphere();
    t_matrix *m = multiply_matrices(scaling(1, 0.5, 1), rotation_z(M_PI/5));
    set_transform(&s6, m);
    t_tuple n6 = normal_at(&s6, point(0, sqrt(2)/2, -sqrt(2)/2));
    t_tuple expected6 = vector(0, 0.97014, -0.24254);
    assert(equal_tuples(n6, expected6, EPSILON));
    printf("Passed: Computing the normal on a transformed sphere\n");

}