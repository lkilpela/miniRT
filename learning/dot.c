#include "tuple.h"

float dot(t_tuple a, t_tuple b)
{

    return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}
void test_dot_product()
{
    t_tuple a = vector(1, 2, 3);
    t_tuple b = vector(2, 3, 4);

    float result = dot(a, b);

    assert(result == 20);
    printf("Dot product test passed\n");
}

