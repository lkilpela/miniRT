#include "structs.h"
# include <math.h>
# include <assert.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

t_matrix *rotation_x(float radians)
{
    t_matrix *m = identity_matrix(4);

    m->data[1][1] = cos(radians);
    m->data[1][2] = -sin(radians);
    m->data[2][1] = sin(radians);
    m->data[2][2] = cos(radians);

    return m;
}

t_matrix *rotation_y(float radians)
{
    t_matrix *m = identity_matrix(4);

    m->data[0][0] = cos(radians);
    m->data[0][2] = sin(radians);
    m->data[2][0] = -sin(radians);
    m->data[2][2] = cos(radians);

    return m;
}

t_matrix *rotation_z(float radians)
{
    t_matrix *m = identity_matrix(4);

    m->data[0][0] = cos(radians);
    m->data[0][1] = -sin(radians);
    m->data[1][0] = sin(radians);
    m->data[1][1] = cos(radians);

    return m;
}

void test_rotate_x_point()
{
    t_tuple p = point(0, 1, 0);
    t_matrix *half_quarter = rotation_x(M_PI / 4);
    t_matrix *inv = inverse(half_quarter);
    
    t_tuple expected_p_halfquarter = point(0, sqrt(2)/2, -sqrt(2)/2);

    t_tuple result = matrix_multiply_tuple(inv, p);

    assert(fabs(result.x - expected_p_halfquarter.x) < EPSILON);
    assert(fabs(result.y - expected_p_halfquarter.y) < EPSILON);
    assert(fabs(result.z - expected_p_halfquarter.z) < EPSILON);

    printf("Rotation around x-axis test passed.\n");

    destroy_matrix(half_quarter);
}

void test_rotate_y_point()
{
    t_tuple p = point(0, 0, 1);
    t_matrix *half_quarter = rotation_y(M_PI / 4);
    t_matrix *full_quarter = rotation_y(M_PI / 2);
    
    t_tuple expected_p_halfquarter = point(sqrt(2)/2, 0, sqrt(2)/2);
    t_tuple result = matrix_multiply_tuple(half_quarter, p);

    assert(fabs(result.x - expected_p_halfquarter.x) < EPSILON);
    assert(fabs(result.y - expected_p_halfquarter.y) < EPSILON);
    assert(fabs(result.z - expected_p_halfquarter.z) < EPSILON);

    t_tuple expected_p_fullquarter = point(1, 0, 0);
    t_tuple result1 = matrix_multiply_tuple(full_quarter, p);

    assert(fabs(result1.x - expected_p_fullquarter.x) < EPSILON);
    assert(fabs(result1.y - expected_p_fullquarter.y) < EPSILON);
    assert(fabs(result1.z - expected_p_fullquarter.z) < EPSILON);


    printf("Rotation around y-axis test passed.\n");

    destroy_matrix(half_quarter);
    destroy_matrix(full_quarter);
}

void test_rotate_z_point()
{
    t_tuple p = point(0, 1, 0);
    t_matrix *half_quarter = rotation_z(M_PI / 4);
    t_matrix *full_quarter = rotation_z(M_PI / 2);
    
    t_tuple expected_p_halfquarter = point(-sqrt(2)/2, sqrt(2)/2, 0);
    t_tuple result = matrix_multiply_tuple(half_quarter, p);

    assert(fabs(result.x - expected_p_halfquarter.x) < EPSILON);
    assert(fabs(result.y - expected_p_halfquarter.y) < EPSILON);
    assert(fabs(result.z - expected_p_halfquarter.z) < EPSILON);

    t_tuple expected_p_fullquarter = point(-1, 0, 0);
    t_tuple result1 = matrix_multiply_tuple(full_quarter, p);

    assert(fabs(result1.x - expected_p_fullquarter.x) < EPSILON);
    assert(fabs(result1.y - expected_p_fullquarter.y) < EPSILON);
    assert(fabs(result1.z - expected_p_fullquarter.z) < EPSILON);


    printf("Rotation around z-axis test passed.\n");

    destroy_matrix(half_quarter);
    destroy_matrix(full_quarter);
}