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