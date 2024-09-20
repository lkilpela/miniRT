#include "structs.h"

// Translating a ray
t_ray transform(t_ray r, t_matrix *m)
{
    t_ray transformed_ray;

    //transformed_ray.origin = multiply_matrices(m, r.origin);

    t_tuple direction = r.direction;
    direction.w = 0;

    transformed_ray.direction = matrix_multiply_tuple(m, r.direction);
    return transformed_ray;
}

void test_ray_translation()
{
    //t_matrix m = translation(5, -3, 2);
}