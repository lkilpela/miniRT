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

t_matrix *combine_rotations(float radians_x, float radians_y, float radians_z)
{
    t_matrix *rotation_x_matrix = rotation_x(radians_x);
    t_matrix *rotation_y_matrix = rotation_y(radians_y);
    t_matrix *rotation_z_matrix = rotation_z(radians_z);

    // Combine rotations: ZYX order
    t_matrix *combined_rotation = matrix_multiply(rotation_z_matrix, rotation_y_matrix);
    t_matrix *final_rotation = matrix_multiply(combined_rotation, rotation_x_matrix);

    // Free intermediate matrices if necessary
    free(rotation_x_matrix);
    free(rotation_y_matrix);
    free(rotation_z_matrix);
    free(combined_rotation);

    return final_rotation;
}
