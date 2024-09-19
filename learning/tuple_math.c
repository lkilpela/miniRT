#include "tuple.h"

t_tuple add(t_tuple a1, t_tuple a2)
{
	t_tuple result;

	result.x = a1.x + a2.x;
	result.y = a1.y + a2.y;
	result.z = a1.z + a2.z;
	result.w = a1.w + a2.w;
	return (result);
}

t_tuple cross(t_tuple a, t_tuple b)
{
    return (vector(
        a.y * b.z - a.z * b.y, //x Component
        a.z * b.x - a.x * b.z, // y Component
        a.x * b.y - a.y * b.x // z Component
        ));
}

// Function to compute the magnitude of a vector
float magnitude(t_tuple v)
{
    return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
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

t_tuple multiply_by_scalar(t_tuple t, float scalar)
{
    t_tuple result;

    result.x = t.x * scalar;
    result.y = t.y * scalar;
    result.z = t.z * scalar;
    result.w = t.w * scalar;
    return (result);
}

float dot(t_tuple a, t_tuple b)
{

    return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
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

t_tuple normalize(t_tuple v)
{
    float mag = magnitude(v);
    return (create_tuple(v.x / mag, v.y / mag, v.z / mag, v.w / mag));
}

