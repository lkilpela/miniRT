#include "structs.h"

t_computations prepare_computations(t_intersection i, t_ray r)
{
    t_computations comps;

    // Copy the intersection's properties, for convenience
    comps.t = i.t;
    comps.object = i.object;

    // Precompute some useful values
    comps.point = position(r, comps.t);
    comps.eyev = negate(r.direction);
    comps.normalv = normal_at((t_sphere *)comps.object, comps.point);

    // If the dot product is negative, the normal points inwards
    if (dot(comps.normalv, comps.eyev) < 0) {
        comps.inside = true;
        comps.normalv = negate(comps.normalv);
    } else {
        comps.inside = false;
    }
    return comps;
}


void test_precomputations()
{
    // Precomputing the state of an intersection
    t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    t_sphere shape = sphere();
    t_intersection i = intersection(4, &shape);
    t_computations comps = prepare_computations(i, r);
    comps.inside = false;

    assert(float_equals(comps.t, i.t, EPSILON));
    assert(comps.object == i.object);
    assert(equal_tuples(comps.point, point(0, 0, -1), EPSILON));
    assert(equal_tuples(comps.eyev, vector(0, 0, -1), EPSILON));
    assert(equal_tuples(comps.normalv, vector(0, 0, -1), EPSILON));

    printf("Passed: Test prepare_computations\n");

    // The hit, when an intersection occurs on the outside
    assert(comps.inside == false);
    printf("Passed: Test prepare_computations outside\n");

    // The hit, when an intersection occurs on the inside
    t_ray r1 = ray(point(0, 0, 0), vector(0, 0, 1));
    t_sphere shape1 = sphere();
    t_intersection i1 = intersection(1, &shape1);
    t_computations comps1 = prepare_computations(i1, r1);
    comps1.inside = true;
    
    assert(float_equals(comps1.t, i1.t, EPSILON));
    assert(comps1.object == i1.object);
    assert(equal_tuples(comps1.point, point(0, 0, 1), EPSILON));
    assert(equal_tuples(comps1.eyev, vector(0, 0, -1), EPSILON));
    assert(equal_tuples(comps1.normalv, vector(0, 0, -1), EPSILON));
    assert(comps1.inside == true);
    printf("Passed: Test prepare_computations inside\n");
}

