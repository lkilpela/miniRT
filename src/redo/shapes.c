#include "structs.h"

/**
 * @brief Initializes a shape with default values.
 * 
 * @return A shape with default transformation matrix and material.
 */
t_shape shape()
{
    t_shape shape;
    shape.transform = identity_matrix(4);
    shape.material = material();
    return shape;
}

/**
 * @brief Transforms a ray into the object's local space.
 * 
 * @param shape The shape to transform the ray for.
 * @param ray The ray to transform.
 * @return The transformed ray.
 */
t_ray transform_ray_to_object_space(t_shape shape, t_ray ray)
{
    t_matrix *inverse_transform = inverse(shape.transform);
    return transform(ray, inverse_transform);
}

/**
 * @brief Transforms a point into the object's local space.
 * 
 * @param shape The shape to transform the point for.
 * @param point The point to transform.
 * @return The transformed point.
 */
t_tuple transform_point_to_object_space(t_shape shape, t_tuple point)
{
    t_matrix *inverse_transform = inverse(shape.transform);
    return matrix_multiply_tuple(inverse_transform, point);
}

/**
 * @brief Transforms a normal vector from object space to world space.
 * 
 * @param shape The shape to transform the normal for.
 * @param normal The normal vector to transform.
 * @return The transformed normal vector.
 */
t_tuple transform_normal_to_world_space(t_shape shape, t_tuple normal)
{
    t_matrix *inverse_transpose = transpose_matrix(inverse(shape.transform));
    t_tuple world_normal = matrix_multiply_tuple(inverse_transpose, normal);
    return normalize(world_normal);
}

void set_transform_shape(t_shape *shape, t_matrix *m)
{
    shape->transform = m;
}


void test_shapes()
{
    // Default shape transformation
    t_shape s = shape();
    assert(matrices_are_equal(s.transform, identity_matrix(4)));
    printf("PASSED: Default shape transformation\n");

    // Assigning a transformation
    set_transform_shape(&s, translation(2, 3, 4));
    assert(matrices_are_equal(s.transform, translation(2, 3, 4)));
    printf("PASSED: Assigning a transformation\n");

    // default material
    t_material m = s.material;
    assert()

}