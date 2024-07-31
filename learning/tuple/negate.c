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

t_tuple negate(t_tuple t)
{
    t_tuple result;

    result.x = -t.x;
    result.y = -t.y;
    result.z = -t.z;
    result.w = -t.w;
    return (result);
}

void test_negate_tuple()
{
    t_tuple a = create_tuple(1, -2, 3, -4);
    t_tuple negated = negate(a);

    assert(equal(negated.x, -1));
    assert(equal(negated.y, 2));
    assert(equal(negated.z, -3));
    assert(equal(negated.w, 4));
    printf("Test negate_tuple: Passed\n");
}

int main()
{
    test_negate_tuple();
}