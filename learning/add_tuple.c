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

t_tuple add(t_tuple a1, t_tuple a2)
{
	t_tuple result;

	result.x = a1.x + a2.x;
	result.y = a1.y + a2.y;
	result.z = a1.z + a2.z;
	result.w = a1.w + a2.w;
	return (result);
}

bool equal_tuple(t_tuple a, t_tuple b)
{
	return (equal(a.x, b.x) && equal(a.y, b.y) 
		&& equal(a.z, b.z) && equal(a.w, b.w));
}

void test_add_tuples()
{
	t_tuple a1 = create_tuple(3, -2, 5, 1);
	t_tuple a2 = create_tuple(-2, 3, 1, 0);
	t_tuple expected = create_tuple(1, 1, 6, 1);
	t_tuple result = add(a1, a2);

	assert(equal_tuple(result, expected));
	printf("Test passed: a1 + a2 = (1, 1, 6, 1)\n");
}

int main()
{
	test_add_tuples();
}