#include "structs.h"
// Translating a ray
t_ray transform(t_ray r, t_matrix m)
{
    t_ray transformed_ray;

    transformed_ray.origin = matrix_multiply_tuple(m, r.origin);

    t_tuple direction = r.direction;
    direction.w = 0;

    transformed_ray.direction = matrix_multiply_tuple(m, r.direction);
    return transformed_ray;
}

void test_ray_translation()
{
    //t_ray r = ray(point(1, 2, 3), vector(0, 1, 0));
    //t_matrix m = translation(3, 4, 5);
}