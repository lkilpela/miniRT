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

t_tuple subtract(t_tuple p1, t_tuple p2)
{
	t_tuple result;

	result.x = p1.x - p2.x;
	result.y = p1.y - p2.y;
	result.z = p1.z - p2.z;
	result.w = p1.w - p2.w;
	return (result);
}

bool equal_tuple(t_tuple a, t_tuple b)
{
	return (equal(a.x, b.x) && equal(a.y, b.y) 
		&& equal(a.z, b.z) && equal(a.w, b.w));
}

void test_subtract_points()
{
	t_tuple p1 = create_tuple(3, 2, 1, 1);
	t_tuple p2 = create_tuple(5, 6, 7, 1);
	t_tuple expected = create_tuple(-2, -4, -6, 0);
	t_tuple result = subtract(p1, p2);

	assert(equal_tuple(result, expected));
	printf("Test passed: p1 - p2 = vector(-2, -4, -6)\n");
}

// Test function for subtracting a vector from a point
void test_subtract_vector_from_point()
{
    t_tuple p = create_tuple(3, 2, 1, 1);
    t_tuple v = create_tuple(5, 6, 7, 0);
    t_tuple expected = create_tuple(-2, -4, -6, 1);
    t_tuple result = subtract(p, v);

    assert(equal_tuple(result, expected));
    printf("Test passed: p - v = point(-2, -4, -6)\n");
}

// Test function for subtracting two vectors
void test_subtract_vectors()
{
    t_tuple v1 = create_tuple(3, 2, 1, 0);
    t_tuple v2 = create_tuple(5, 6, 7, 0);
    t_tuple expected = create_tuple(-2, -4, -6, 0);
    t_tuple result = subtract(v1, v2);

    assert(equal_tuple(result, expected));
    printf("Test passed: v1 - v2 = vector(-2, -4, -6)\n");
}

int main()
{
	test_subtract_points();
    test_subtract_vector_from_point();
    test_subtract_vectors();
}