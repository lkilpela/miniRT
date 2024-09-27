#include "structs.h"

/* TUPLE UTILS */

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

bool equal_tuples(t_tuple a, t_tuple b, float epsilon)
{
    return fabs(a.x - b.x) < epsilon && fabs(a.y - b.y) < epsilon && fabs(a.z - b.z) < epsilon && fabs(a.w - b.w) < epsilon;
}

void print_tuple_p(t_tuple t)
{
    printf("(%f, %f, %f, %f)\n", t.x, t.y, t.z, 1.0);
}

void print_tuple_v(t_tuple t)
{
    printf("(%f, %f, %f, %f)\n", t.x, t.y, t.z, 0.0);
}

// Function to check if a tuple is a point
bool	is_point(t_tuple t)
{
	return (equal(t.w, 1.0));
}

// Function to check if a tuple is a vector
bool	is_vector(t_tuple t)
{
	return (equal(t.w, 0.0));
}

// Function to compare two floating-point numbers with a tolerance
bool float_equals(float a, float b, float epsilon) {
    return fabs(a - b) < epsilon;
}
