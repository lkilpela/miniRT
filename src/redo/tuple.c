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

// Factory function to create a point
t_tuple point(float x, float y, float z)
{
    return (create_tuple(x, y, z, 1.0));
}

// Function to compare two floating point numbers
bool equal(float a, float b)
{
    return (fabs(a - b) < EPSILON);
}

bool equal_tuple(t_tuple a, t_tuple b)
{
	return (equal(a.x, b.x) && equal(a.y, b.y) 
		&& equal(a.z, b.z) && equal(a.w, b.w));
}

// Factory function to create a vector
t_tuple vector(float x, float y, float z)
{
    return (create_tuple(x, y, z, 0.0));
}

// Function to check if a tuple is a point
bool is_point(t_tuple t)
{
    return (equal(t.w, 1.0));
}

// Function to check if a tuple is a vector
bool is_vector(t_tuple t)
{
    return (equal(t.w, 0.0));
}

bool tuples_are_equal(t_tuple a, t_tuple b, float epsilon)
{
    return fabs(a.x - b.x) < epsilon && fabs(a.y - b.y) < epsilon && fabs(a.z - b.z) < epsilon && fabs(a.w - b.w) < epsilon;
}

void print_tuple(t_tuple t)
{
    printf("(%f, %f, %f, %f)\n", t.x, t.y, t.z, t.w);
}

void test_tuple_with_w_is_point()
{
    t_tuple a = create_tuple(4.3, -4.2, 3.1, 1.0);

    assert(equal(a.x, 4.3));
    assert(equal(a.y, -4.2));
    assert(equal(a.z, 3.1));
    assert(equal(a.w, 1.0));
    assert(is_point(a) == true);
    assert(is_vector(a) == false);
    printf("test_tuple_with_w_is_point passed\n");
}

void test_tuple_with_w_is_vector()
{
    t_tuple a = create_tuple(4.3, -4.2, 3.1, 0.0);

    assert(equal(a.x, 4.3));
    assert(equal(a.y, -4.2));
    assert(equal(a.z, 3.1));
    assert(equal(a.w, 0.0));
    assert(is_point(a) == false);
    assert(is_vector(a) == true);
    printf("test_tuple_with_w_is_vector passed\n");
}

void test_point_function()
{
    t_tuple p = point(4, -4, 3);
    
    assert(equal(p.x, 4));
    assert(equal(p.y, -4));
    assert(equal(p.z, 3));
    assert(equal(p.w, 1.0));

    printf("test_point_function passed\n");
}

void test_vector_function()
{
    t_tuple v = vector(4, -4, 3);
    
    assert(equal(v.x, 4));
    assert(equal(v.y, -4));
    assert(equal(v.z, 3));
    assert(equal(v.w, 0.0));

    printf("test_vector_function passed\n");
}

/*int main() 
{
    test_tuple_with_w_is_point();
    test_tuple_with_w_is_vector();
    test_point_function();
    test_vector_function();
    
    return 0;
}*/