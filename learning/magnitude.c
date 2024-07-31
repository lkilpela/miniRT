#include "tuple.h"

t_tuple create_tuple(float x, float y, float z, float w)
{
    t_tuple t;

    t.x = x;
    t.y = y;
    t.z = z;
    t.w = w;
    return (t);
}

bool equal(float a, float b)
{
    return (fabs(a - b) < EPSILON);
}

// Factory function to create a vector
t_tuple vector(float x, float y, float z)
{
    return (create_tuple(x, y, z, 0.0));
}

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
