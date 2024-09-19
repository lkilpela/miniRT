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

/*void test_ray()
{
    t_tuple origin = point(2, 3, 4);
    t_tuple direction = vector(1, 0, 0);
    t_ray r = create_ray(origin, direction);
    t_tuple p = position(r, 0);
    assert(equal_tuple(p, origin));
    p = position(r, 1);
    assert(equal_tuple(p, point(3, 3, 4)));
    p = position(r, -1);
    assert(equal_tuple(p, point(1, 3, 4)));
    p = position(r, 2.5);
    assert(equal_tuple(p, point(4.5, 3, 4)));
    printf("All tests passed\n");
}*/