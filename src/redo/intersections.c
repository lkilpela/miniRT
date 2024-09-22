#include "structs.h"

typedef struct s_object
{
    int id;
    t_matrix transform;
    t_material material;
} t_object;

typedef struct s_computations
{
    double t;
    t_object *object;
    t_tuple point;
    t_tuple eyev;
    t_tuple normalv;
} t_computations;


t_computations prepare_computations(t_intersection i, t_ray r)
{
    t_computations comps;
    comps.t = i.t;
    comps.object = i.object;
    comps.point = position(r, comps.t);
    comps.eyev = negate(r.direction);
    comps.normalv = normal_at((t_sphere *)comps.object, comps.point);
    return comps;
}

void test_precomputations()
{
    t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    t_sphere shape = sphere();
    t_intersection i = intersection(4, &shape);
    t_computations comps = prepare_computations(i, r);

    assert(float_equals(comps.t, i.t, EPSILON));
    assert(comps.object == i.object);
    assert(equal_tuples(comps.point, point(0, 0, -1), EPSILON));
    assert(equal_tuples(comps.eyev, vector(0, 0, -1), EPSILON));
    assert(equal_tuples(comps.normalv, vector(0, 0, -1), EPSILON));

    printf("Passed: Test prepare_computations\n");
}