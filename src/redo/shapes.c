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

/**
 * @brief Calculates the intersections of a ray and a shape.
 * 
 * @param shape The shape to intersect with.
 * @param ray The ray to intersect.
 * @return The intersections of the ray and the shape.
 */
t_intersections intersect(t_shape *shape, t_ray ray)
{
    t_matrix *inverse_transform = inverse(shape->transform);
    t_ray local_ray = transform(ray, inverse_transform);
    return shape->local_intersect(shape, local_ray);
}

/**
 * @brief Calculates the normal at a given point on a shape.
 * 
 * @param shape The shape to calculate the normal for.
 * @param point The point at which to calculate the normal.
 * @return The normal vector at the given point.
 */
t_tuple normal_at(t_shape *shape, t_tuple point)
{
    t_matrix *inverse_transform = inverse(shape->transform);
    t_tuple local_point = matrix_multiply_tuple(inverse_transform, point);
    t_tuple local_normal = shape->local_normal_at(shape, local_point);
    t_matrix *transpose_inverse_transform = transpose(inverse_transform);
    t_tuple world_normal = matrix_multiply_tuple(transpose_inverse_transform, local_normal);
    world_normal.w = 0;
    return normalize(world_normal);
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
    printf("Material values: %f %f %f %f %f %f %f\n", m.color.r, m.color.g, m.color.b, m.ambient, m.diffuse, m.specular, m.shininess);

    // Assigning a material
    t_material m2 = material();
    m2.ambient = 1;
    s.material = m2;
    assert(color_equal(s.material.color, color(1, 1, 1), EPSILON));
    assert(float_equals(s.material.ambient, 1, EPSILON));
    assert(float_equals(s.material.diffuse, 0.9, EPSILON));
    assert(float_equals(s.material.specular, 0.9, EPSILON));
    assert(float_equals(s.material.shininess, 200, EPSILON));
    printf("PASSED: Assigning a material\n");
}