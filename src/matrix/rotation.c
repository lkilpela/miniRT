#include "structs.h"

t_matrix	*rotation_x(float radians)
{
	t_matrix *m;

	m = identity_matrix(4);

	m->data[1][1] = cos(radians);
	m->data[1][2] = -sin(radians);
	m->data[2][1] = sin(radians);
	m->data[2][2] = cos(radians);
	return (m);
}

t_matrix	*rotation_y(float radians)
{
    t_matrix *m;

	m = identity_matrix(4);
    m->data[0][0] = cos(radians);
    m->data[0][2] = sin(radians);
    m->data[2][0] = -sin(radians);
    m->data[2][2] = cos(radians);
    return (m);
}

t_matrix	*rotation_z(float radians)
{
	t_matrix *m;

	m = identity_matrix(4);
	m->data[0][0] = cos(radians);
	m->data[0][1] = -sin(radians);
	m->data[1][0] = sin(radians);
	m->data[1][1] = cos(radians);
	return (m);
}

t_matrix	*combine_rotations(float radians_x, float radians_y, float radians_z)
{
	t_matrix *rotation_x_matrix;
	t_matrix *rotation_y_matrix;
	t_matrix *rotation_z_matrix;
	t_matrix *rotation_zy;
	t_matrix *combined_rotation;

	rotation_x_matrix = rotation_x(radians_x);
	rotation_y_matrix = rotation_y(radians_y);
	rotation_z_matrix = rotation_z(radians_z);

	// Combine rotations: ZYX order
	rotation_zy = multiply_matrices(rotation_z_matrix, rotation_y_matrix);
	combined_rotation =  multiply_matrices(rotation_zy, rotation_x_matrix);

	// Free intermediate matrices if necessary
	destroy_matrix(rotation_x_matrix);
	destroy_matrix(rotation_y_matrix);
	destroy_matrix(rotation_z_matrix);
	destroy_matrix(rotation_zy);

	return (combined_rotation);
}
