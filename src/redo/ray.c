#include "structs.h"

t_ray ray(t_tuple origin, t_tuple direction)
{
    t_ray r;

    r.origin = origin;
    r.direction = direction;
    return (r);
}

t_tuple position(t_ray r, float t)
{
    return (add(r.origin, multiply_by_scalar(r.direction, t)));
}

// Translating a ray
t_ray transform(t_ray r, t_matrix *m)
{
    t_ray transformed_ray;

    //transformed_ray.origin = multiply_matrices(m, r.origin);

    t_tuple direction = r.direction;
    direction.w = 0;

    transformed_ray.direction = matrix_multiply_tuple(m, r.direction);
    return transformed_ray;
}

void test_ray()
{
    // Creating and querying a ray
    t_tuple origin = point(1, 2, 3);
    t_tuple direction = vector(4, 5, 6);
    t_ray r = ray(origin, direction);
    assert(equal_tuple(r.origin, origin));
    assert(equal_tuple(r.direction, direction));
    printf("Passed: Creating and querying a ray\n");
    
    // Computing a point from a distance
    t_tuple origin1 = point(2, 3, 4);
    t_tuple direction1 = vector(1, 0, 0);
    t_ray r1 = ray(origin1, direction1);

    t_tuple expected_p1 = point(2, 3, 4);
    t_tuple p1 = position(r1, 0);
    assert(equal_tuple(p1, expected_p1));

    t_tuple expected_p2 = point(3, 3, 4);
    t_tuple p2 = position(r1, 1);
    assert(equal_tuple(p2, expected_p2));

    t_tuple expected_p3 = point(1, 3, 4);
    t_tuple p3 = position(r1, -1);
    assert(equal_tuple(p3, expected_p3));

    t_tuple expected_p4 = point(4.5, 3, 4);
    t_tuple p4 = position(r1, 2.5);
    assert(equal_tuple(p4, expected_p4));
    printf("Passed: Computing a point from a distance\n");

    // Translating a ray
    t_ray r2 = ray(point(1, 2, 3), vector(0, 1, 0));
    t_matrix *m = translation(3, 4, 5);
    t_ray r2_translated = transform(r2, m);
    assert(equal_tuples(r2_translated.origin, point(4, 6, 8), EPSILON));
    assert(equal_tuples(r2_translated.direction, vector(0, 1, 0), EPSILON));
    printf("Passed: Translating a ray\n");

}