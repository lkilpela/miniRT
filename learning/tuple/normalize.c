#include "tuple.h"

t_tuple normalize(t_tuple v)
{
    float mag = magnitude(v);
    return (create_tuple(v.x / mag, v.y / mag, v.z / mag, v.w / mag));
}

void test_normalize()
{
    t_tuple v1 = vector(4, 0, 0);
    t_tuple v2 = vector(1, 2, 3);

    t_tuple norm_v1 = normalize(v1);
    t_tuple norm_v2 = normalize(v2);

    assert(equal_tuple(norm_v1, vector(1.0, 0.0, 0.0)));
    assert(equal_tuple(norm_v2, vector(1.0 / sqrt(14.0), 2.0 / sqrt(14.0), 3.0 / sqrt(14.0))));

    assert(equal(magnitude(norm_v2), 1.0));
    printf("All normalization tests passed.\n");
}
