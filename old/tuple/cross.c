#include "/Users/lumik/miniRT_learning/learning/tuple.h"

t_tuple cross(t_tuple a, t_tuple b)
{
    return (vector(
        a.y * b.z - a.z * b.y, //x Component
        a.z * b.x - a.x * b.z, // y Component
        a.x * b.y - a.y * b.x // z Component
        ));
}
void test_cross_product()
{
    t_tuple a = vector(1, 2, 3);
    t_tuple b = vector(2, 3, 4);
    t_tuple result1 = cross(a, b);
    t_tuple result2 = cross(b, a);

    assert(equal_tuple(result1, vector(-1, 2, -1)));
    assert(equal_tuple(result2, vector(1, -2, 1)));

    printf("Cross product test passed.\n");
}