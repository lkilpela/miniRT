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