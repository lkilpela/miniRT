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
    shape.object = NULL;
    shape.local_normal_at = NULL;
    shape.local_intersect = NULL;
    shape.saved_ray.origin = point(0, 0, 0);
    shape.saved_ray.direction = vector(0, 0, 0);
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

bool is_zero_vector(t_tuple t)
{
    return (t.x == 0 && t.y == 0 && t.z == 0 && t.w == 0);
}

bool is_valid_ray(t_ray ray)
{
    return !(is_zero_vector(ray.origin) && is_zero_vector(ray.direction));
}

/**
 * @brief Calculates the intersections of a ray and a shape.
 * 
 * @param shape The shape to intersect with.
 * @param ray The ray to intersect.
 * @return The intersections of the ray and the shape.
 */
t_intersections intersect_shape(t_shape *shape, t_ray ray)
{
    if (shape == NULL || !is_valid_ray(ray))
    {
        fprintf(stderr, "Error: intersect_shape: shape or ray is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (shape->local_intersect == NULL)
    {
        fprintf(stderr, "Error: intersect_shape: local_intersect is NULL\n");
        exit(EXIT_FAILURE);
    }
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
t_tuple normal_at_shape(t_shape *shape, t_tuple point)
{
    t_matrix *inverse_transform = inverse(shape->transform);
    t_tuple local_point = matrix_multiply_tuple(inverse_transform, point);
    t_tuple local_normal = shape->local_normal_at(shape, local_point);
    t_matrix *transpose_inverse_transform = transpose_matrix(inverse_transform);
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

    // Intersecting a scaled shape with a ray
    t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    t_sphere_new s2 = sphere_new();
        //Use the base field to access the shape
    t_shape sh = s2.base;
    set_transform_shape(&sh, scaling(2, 2, 2));
    t_intersections xs = intersect_shape(&sh, r);
    printf("Intersections: %d\n", xs.count); // Example usage
    assert(equal_tuples(sh.saved_ray.origin, point(0, 0, -2.5), EPSILON));
    printf("PASSED: Intersecting a scaled shape with a ray\n");

    // Intersecting a translated shape with a ray
    t_sphere_new s3 = sphere_new();
    t_shape sh2 = s3.base;
    set_transform_shape(&sh2, translation(5, 0, 0));
    t_intersections xs2 = intersect_shape(&sh2, r);
    printf("Intersections: %d\n", xs2.count); // Example usage
    assert(equal_tuples(sh2.saved_ray.origin, point(-5, 0, -5), EPSILON));
    assert(equal_tuples(sh2.saved_ray.direction, vector(0, 0, 1), EPSILON));
    printf("PASSED: Intersecting a translated shape with a ray\n");


}