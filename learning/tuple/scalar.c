#include "/Users/lumik/miniRT_learning/learning/tuple.h"

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

bool equal_tuple(t_tuple a, t_tuple b)
{
	return (equal(a.x, b.x) && equal(a.y, b.y) 
		&& equal(a.z, b.z) && equal(a.w, b.w));
}

t_tuple multiply_by_scalar(t_tuple t, float scalar)
{
    t_tuple result;

    result.x = t.x * scalar;
    result.y = t.y * scalar;
    result.z = t.z * scalar;
    result.w = t.w * scalar;
    return (result);
}

t_tuple multiply_by_fraction(t_tuple t, float scalar)
{
    t_tuple result;

    result.x = t.x * scalar;
    result.y = t.y * scalar;
    result.z = t.z * scalar;
    result.w = t.w * scalar;
    return (result);
}

t_tuple divide_by_scalar(t_tuple t, float scalar)
{
    t_tuple result;

    result.x = t.x / scalar;
    result.y = t.y / scalar;
    result.z = t.z / scalar;
    result.w = t.w / scalar;
    return (result);
}

void test_tuple_by_scalar()
{
    t_tuple a = create_tuple(1, -2, 3, -4);
    t_tuple expected1 = create_tuple(3.5, -7, 10.5, -14);
    t_tuple expected2 = create_tuple(0.5, -1, 1.5, -2);
    t_tuple result1 = multiply_by_scalar(a, 3.5);
    t_tuple result2 = multiply_by_fraction(a, 0.5);
    t_tuple result3 = divide_by_scalar(a, 2);
    assert(equal_tuple(result1, expected1));
    assert(equal_tuple(result2, expected2));
    assert(equal_tuple(result3, expected2));

    printf("Test: Passed\n");
}

int main()
{
    test_tuple_by_scalar();
}