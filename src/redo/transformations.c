#include "structs.h"

/* TRANSLATION
** Return a 4x4 translation matrix
** Set the translation values:
** - in the last column of the 4x4 matrix,
** which shifts points by (x, y, z) when the matrix is applied.
** translation(5, -3, 2), the matrix will be:
| 1  0  0  5  |
| 0  1  0  -3 |
| 0  0  1  2  |
| 0  0  0  1  |
            ^ set translation values
*/
t_matrix *translation(float x, float y, float z)
{
    t_matrix *m = identity_matrix(4);

    // Set translation values
    m->data[0][3] = x;
    m->data[1][3] = y;
    m->data[2][3] = z;

    return m;
}

/* SCALING
** Return a 4x4 scaling matrix
*/
t_matrix *scaling(float x, float y, float z)
{
    t_matrix *m = identity_matrix(4);

    // Set scaling values
    m->data[0][0] = x;
    m->data[1][0] = 0;
    m->data[2][0] = 0;
    m->data[3][0] = 0;

    m->data[0][1] = 0;
    m->data[1][1] = y;
    m->data[2][1] = 0;
    m->data[3][1] = 0;

    m->data[0][2] = 0;
    m->data[1][2] = 0;
    m->data[2][2] = z;
    m->data[3][2] = 0;

    m->data[0][3] = 0;
    m->data[1][3] = 0;
    m->data[2][3] = 0;
    m->data[3][3] = 1;

    return m;
}

/* SHEARING
** The effect of making straight lines not slanted.
** For example: x is initially 2, but moving x in proportion to y adds 1 times y (or 3) to x (2) 
and produces a new x of 5.
** Check test_shearing() for more examples
*/
t_matrix *shearing(float xy, float xz, float yx, float yz, float zx, float zy)
{
    t_matrix *m = identity_matrix(4);

    m->data[0][1] = xy; // x moved in proportion to y
    m->data[0][2] = xz; // x moved in proportion to z
    m->data[1][0] = yx; // y moved in proportion to x
    m->data[1][2] = yz; // y moved in proportion to z
    m->data[2][0] = zx; // z moved in proportion to x
    m->data[2][1] = zy; // z moved in proportion to y

    return m;
}

/* DEFINING VIEW TRANSFORMATION 
** Pretends the eye moves instead of the world
** - Specify where you want the eye to be in the scene (from)
** - Specify where you want the eye to look at (to)
** - Specify the direction of the up vector (up)
** - Return a view transformation matrix
*/
t_matrix *view_transform(t_tuple from, t_tuple to, t_tuple up)
{

    // Debug print
    //printf("View Transform: \n");
    //print_tuple(from);
    //print_tuple(to);
    //print_tuple(up);

    t_tuple forward = normalize(subtract(to, from));
    t_tuple left = cross(forward, normalize(up));
    t_tuple true_up = cross(left, forward);

    //print_tuple(forward);
    //print_tuple(left);
    //print_tuple(true_up);

    t_matrix *orientation = identity_matrix(4);
    orientation->data[0][0] = left.x;
    orientation->data[0][1] = left.y;
    orientation->data[0][2] = left.z;
    orientation->data[1][0] = true_up.x;
    orientation->data[1][1] = true_up.y;
    orientation->data[1][2] = true_up.z;
    orientation->data[2][0] = -forward.x;
    orientation->data[2][1] = -forward.y;
    orientation->data[2][2] = -forward.z;

    return multiply_matrices(orientation, translation(-from.x, -from.y, -from.z));
}

void test_myltiply_by_translation()
{
    t_matrix *transform = translation(5, -3, 2);
    t_tuple p = point(-3, 4, 5);
    t_tuple expected = point(2, 1, 7);

    t_tuple result = matrix_multiply_tuple(transform, p);

    assert(result.x == expected.x);
    assert(result.y == expected.y);
    assert(result.z == expected.z);

    printf("Passed\n");

    destroy_matrix(transform);
}

void test_myltiply_by_inverse_translation()
{
    t_matrix *transform = translation(5, -3, 2);
    t_matrix *inv = inverse(transform);
    t_tuple p = point(-3, 4, 5);

    t_tuple expected = point(-8, 7, 3);

    t_tuple result = matrix_multiply_tuple(inv, p);
        
    assert(result.x == expected.x);
    assert(result.y == expected.y);
    assert(result.z == expected.z);

    printf("Passed: test_myltiply_by_inverse_translation\n");

    destroy_matrix(transform);
    destroy_matrix(inv);
}

void test_translation_doesnot_affect_vector()
{
    t_matrix *transform = translation(5, -3, 2);
    t_tuple v = vector(-3, 4, 5);

    t_tuple expected = vector(-3, 4, 5);

    t_tuple result = matrix_multiply_tuple(transform, v);
        
    assert(result.x == expected.x);
    assert(result.y == expected.y);
    assert(result.z == expected.z);

    printf("Passed: test_translation_doesnot_affect_vector\n");

    destroy_matrix(transform);
}

void test_scaling_applied_to_point()
{
    t_matrix *transform = scaling(2, 3, 4);
    t_tuple p = point(-4, 6, 8);

    t_tuple expected = point(-8, 18, 32);

    t_tuple result = matrix_multiply_tuple(transform, p);
        
    assert(result.x == expected.x);
    assert(result.y == expected.y);
    assert(result.z == expected.z);

    printf("Passed: test_scaling_applied_to_point\n");

    destroy_matrix(transform);
}

void test_scaling_applied_to_vector()
{
    t_matrix *transform = scaling(2, 3, 4);
    t_tuple v = vector(-4, 6, 8);

    t_tuple expected = point(-8, 18, 32);

    t_tuple result = matrix_multiply_tuple(transform, v);
        
    assert(result.x == expected.x);
    assert(result.y == expected.y);
    assert(result.z == expected.z);

    printf("Passed: test_scaling_applied_to_vector\n");

    destroy_matrix(transform);
}

/* MULTIPLYING A TUPLE BY THE INVERSE OF A SCALING MATRIX
** -> Scale the tuple in opposite way (shringking instead of growing, or vice versa)
*/
void test_multiplying_by_inverse_scaling()
{
    t_matrix *transform = scaling(2, 3, 4);
    t_matrix *inv = inverse(transform);
    t_tuple v = vector(-4, 6, 8);

    t_tuple expected = vector(-2, 2, 2);

    t_tuple result = matrix_multiply_tuple(inv, v);
        
    assert(result.x == expected.x);
    assert(result.y == expected.y);
    assert(result.z == expected.z);

    printf("Passed: test_multiplying_by_inverse_scaling\n");

    destroy_matrix(transform);
}

/* REFLECTION IS SCALING BY A NEGATIVE VALUE
** A point can be reflected across the x axis by scaling the x component by -1
** the point was moved from the positive side of the x axis, to the negative
*/
void test_reflection_is_scaling_by_negative_value()
{
    t_matrix *transform = scaling(-1, 1, 1);
    t_tuple p = point(2, 3, 4);

    t_tuple expected = point(-2, 3, 4);

    t_tuple result = matrix_multiply_tuple(transform, p);
        
    assert(result.x == expected.x);
    assert(result.y == expected.y);
    assert(result.z == expected.z);

    printf("Passed: test_reflection_is_scaling_by_negative_value\n");

    destroy_matrix(transform);
}

void test_shearing()
{
    // A shearing transformation moves x in proportion to y
    t_matrix *transform_xy = shearing(1, 0, 0, 0, 0, 0);
    t_tuple p_xy = point(2, 3, 4);
    t_tuple expected_xy = point(5, 3, 4);
    t_tuple result_xy = matrix_multiply_tuple(transform_xy, p_xy);
    assert(result_xy.x == expected_xy.x);
    assert(result_xy.y == expected_xy.y);
    assert(result_xy.z == expected_xy.z);
    printf("Passed: A shearing transformation moves x in proportion to y\n");

    // A shearing transformation moves x in proportion to z
    t_matrix *transform_xz = shearing(0, 1, 0, 0, 0, 0);
    t_tuple p_xz = point(2, 3, 4);
    t_tuple expected_xz = point(6, 3, 4);
    t_tuple result_xz = matrix_multiply_tuple(transform_xz, p_xz);
    assert(result_xz.x == expected_xz.x);
    assert(result_xz.y == expected_xz.y);
    assert(result_xz.z == expected_xz.z);
    printf("Passed: A shearing transformation moves x in proportion to z\n");

    // A shearing transformation moves y in proportion to x
    t_matrix *transform_yx = shearing(0, 0, 1, 0, 0, 0);
    t_tuple p_yx = point(2, 3, 4);
    t_tuple expected_yx = point(2, 5, 4);
    t_tuple result_yx = matrix_multiply_tuple(transform_yx, p_yx);
    assert(result_yx.x == expected_yx.x);
    assert(result_yx.y == expected_yx.y);
    assert(result_yx.z == expected_yx.z);
    printf("Passed: A shearing transformation moves y in proportion to x\n");

    // A shearing transformation moves y in proportion to z
    t_matrix *transform_yz = shearing(0, 0, 0, 1, 0, 0);
    t_tuple p_yz = point(2, 3, 4);
    t_tuple expected_yz = point(2, 7, 4);
    t_tuple result_yz = matrix_multiply_tuple(transform_yz, p_yz);
    assert(result_yz.x == expected_yz.x);
    assert(result_yz.y == expected_yz.y);
    assert(result_yz.z == expected_yz.z);
    printf("Passed: A shearing transformation moves y in proportion to z\n");

    // A shearing transformation moves z in proportion to x
    t_matrix *transform_zx = shearing(0, 0, 0, 0, 1, 0);
    t_tuple p_zx = point(2, 3, 4);
    t_tuple expected_zx = point(2, 3, 6);
    t_tuple result_zx = matrix_multiply_tuple(transform_zx, p_zx);
    assert(result_zx.x == expected_zx.x);
    assert(result_zx.y == expected_zx.y);
    assert(result_zx.z == expected_zx.z);
    printf("Passed: A shearing transformation moves z in proportion to x\n");

    // A shearing transformation moves z in proportion to y
    t_matrix *transform_zy = shearing(0, 0, 0, 0, 0, 1);
    t_tuple p_zy = point(2, 3, 4);
    t_tuple expected_zy = point(2, 3, 7);
    t_tuple result_zy = matrix_multiply_tuple(transform_zy, p_zy);
    assert(result_zy.x == expected_zy.x);
    assert(result_zy.y == expected_zy.y);
    assert(result_zy.z == expected_zy.z);
    printf("Passed: A shearing transformation moves z in proportion to y\n");
}

void test_chaining_transformations()
{
    // Test: Individual transformations are applied in sequence
    t_tuple p = point(1, 0, 1);
    t_matrix *A = rotation_x(M_PI / 2);
    t_matrix *B = scaling(5, 5, 5);
    t_matrix *C = translation(10, 5, 7);

    // Apply rotation first
    t_tuple p2 = matrix_multiply_tuple(A, p);
    t_tuple expected_p2 = point(1, -1, 0);
    assert(equal_tuples(p2, expected_p2, EPSILON));

    // Apply scaling next
    t_tuple p3 = matrix_multiply_tuple(B, p2);
    t_tuple expected_p3 = point(5, -5, 0);
    assert(equal_tuples(p3, expected_p3, EPSILON));

    // Apply translation last
    t_tuple p4 = matrix_multiply_tuple(C, p3);
    t_tuple expected_p4 = point(15, 0, 7);
    assert(equal_tuples(p4, expected_p4, EPSILON));

    // Test: Chained transformations are applied in reverse order
    t_matrix *T = multiply_matrices(C, multiply_matrices(B, A));
    t_tuple p5 = matrix_multiply_tuple(T, p);
    t_tuple expected_p5 = point(15, 0, 7);
    assert(equal_tuples(p5, expected_p5, EPSILON));

    printf("Passed: test_chainig_transformations\n");

    destroy_matrix(A);
    destroy_matrix(B);
    destroy_matrix(C);
    destroy_matrix(T);
}

void test_view_transformation()
{
    // Test: The transformation matrix for the default orientation
    t_tuple from = point(0, 0, 0);
    t_tuple to = point(0, 0, -1);
    t_tuple up = vector(0, 1, 0);
    t_matrix *t = view_transform(from, to, up);
    assert(matrices_are_equal(t, identity_matrix(4)));

    // Test: A view transformation matrix looking in positive z direction
    t_tuple from1 = point(0, 0, 0);
    t_tuple to1 = point(0, 0, 1);
    t_tuple up1 = vector(0, 1, 0);
    t_matrix *t1 = view_transform(from1, to1, up1);
    t_matrix *expected_t1 = scaling(-1, 1, -1);
    assert(matrices_are_equal(t1, expected_t1));

    // Test: The view transformation moves the world
    t_tuple from2 = point(0, 0, 8);
    t_tuple to2 = point(0, 0, 0);
    t_tuple up2 = vector(0, 1, 0);
    t_matrix *t2 = view_transform(from2, to2, up2);
    t_matrix *expected_t2 = translation(0, 0, -8);
    assert(matrices_are_equal(t2, expected_t2));

    // Test: An arbitrary view transformation
    t_tuple from3 = point(1, 3, 2);
    t_tuple to3 = point(4, -2, 8);
    t_tuple up3 = vector(1, 1, 0);
    t_matrix *t3 = view_transform(from3, to3, up3);
    float values_t3[4][4] = {
        {-0.50709, 0.50709, 0.67612, -2.36643},
        {0.76772, 0.60609, 0.12122, -2.82843},
        {-0.35857, 0.59761, -0.71714, 0.00000},
        {0.00000, 0.00000, 0.00000, 1.00000}
    };
    t_matrix *expected_t3 = create_matrix(4, 4, values_t3);
    assert(matrices_are_equal(t3, expected_t3));
    printf("Passed: test_view_transformation\n");
}