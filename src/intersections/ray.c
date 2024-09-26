#include "structs.h"

t_ray ray(t_tuple origin, t_tuple direction)
{
    t_ray r;

    r.origin = origin;
    r.direction = direction;
    return (r);
}

t_tuple position(t_ray r, float t)
{
    //printf("Ray: Origin: %f %f %f, Direction: %f %f %f\n", r.origin.x, r.origin.y, r.origin.z, r.direction.x, r.direction.y, r.direction.z);
    //printf("T: %f\n", t);
    t_tuple result = add(r.origin, multiply_by_scalar(r.direction, t));
    //printf("result: %f %f %f\n", result.x, result.y, result.z);
    return result;
}

// Translating a ray
t_ray transform(t_ray r, t_matrix *m)
{
    t_ray transformed_ray;

    transformed_ray.origin = matrix_multiply_tuple(m, r.origin);

    t_tuple direction = r.direction;
    direction.w = 0;

    transformed_ray.direction = matrix_multiply_tuple(m, r.direction);
    return transformed_ray;
}
