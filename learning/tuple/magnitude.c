#include "/Users/lumik/miniRT_learning/learning/tuple.h"

// Function to compute the magnitude of a vector
float magnitude(t_tuple v)
{
    return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

void test_magnitude_vector()
{
    t_tuple v1 = vector(1, 0, 0);
    t_tuple v2 = vector(0, 1, 0);
    t_tuple v3 = vector(0, 0, 1);
    t_tuple v4 = vector(1, 2, 3);
    t_tuple v5 = vector(-1, -2, -3);
    assert(equal(magnitude(v1), 1.0));
    assert(equal(magnitude(v2), 1.0));
    assert(equal(magnitude(v3), 1.0));
    assert(equal(magnitude(v4), sqrt(14.0)));
    assert(equal(magnitude(v5), sqrt(14.0)));

    printf("All magnitude tests passed.\n");
}

