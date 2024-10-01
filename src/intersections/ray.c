#include "structs.h"

t_ray	ray(t_tuple origin, t_tuple direction)
{
	t_ray	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

t_tuple	position(t_ray r, float t)
{
	t_tuple	result;

	result = add(r.origin, multiply_by_scalar(r.direction, t));
	return (result);
}

// Translating a ray
t_ray	transform(t_ray r, t_matrix *m)
{
	t_ray	transformed_ray;
	t_tuple	direction;

	transformed_ray.origin = matrix_multiply_tuple(m, r.origin);
	direction = r.direction;
	direction.w = 0;
	transformed_ray.direction = matrix_multiply_tuple(m, r.direction);
	return (transformed_ray);
}
