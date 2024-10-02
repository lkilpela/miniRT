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

/* // Calculate the necessary rotations around the x, y, and z axes 
// to align the default normal with the given normal.
//    -  determining the angles required for each axis
//       and then combining these rotations.
t_matrix	*align_with_normal(t_tuple normal)
{
	double		radians_x;
	double		radians_z;
	t_matrix	*rotation_matrix;

    // Normalize the given normal vector
    normal = normalize(normal);

    // Calculate the angle required to align the y-component of the default normal (0, 1, 0) with the y-component of the given normal.
    radians_x = acos(dot(vector(0, 1, 0), vector(0, normal.y, normal.z)));
    if (normal.z < 0)
        radians_x = -radians_x;

    // Calculate the angle required to align the x-component of the default normal (1, 0, 0) with the x-component of the given normal.
    radians_z = acos(dot(vector(1, 0, 0), vector(normal.x, normal.y, 0)));
    if (normal.x < 0)
        radians_z = -radians_z;

    // Combine the rotations
    rotation_matrix = combine_rotations(radians_x, 0, radians_z);

    return (rotation_matrix);
}

/* Function calculates a rotation matrix that rotates a vector around a given
** axis by a specified angle. This is typically done using the axis-angle 
** rotation formula, which is a common method in 3D graphics for rotating 
** vectors around arbitrary axes.

t_matrix *rotation_around_axis(t_tuple axis, double angle)
{
	// Calculate Trigonometric Values: Compute the cosine and sine of the angle, as well as 1 - cos(angle).
    double cos_theta = cos(angle);
    double sin_theta = sin(angle);
    double one_minus_cos = 1.0 - cos_theta;

    // Normalize the axis vector
    axis = normalize(axis);

    double x = axis.x;
    double y = axis.y;
    double z = axis.z;

	// Construct the Rotation Matrix: Use the axis-angle rotation formula to fill in the elements of the rotation matrix.

    t_matrix *rotation_matrix = identity_matrix(4);

    rotation_matrix->data[0][0] = cos_theta + x * x * one_minus_cos;
    rotation_matrix->data[0][1] = x * y * one_minus_cos - z * sin_theta;
    rotation_matrix->data[0][2] = x * z * one_minus_cos + y * sin_theta;

    rotation_matrix->data[1][0] = y * x * one_minus_cos + z * sin_theta;
    rotation_matrix->data[1][1] = cos_theta + y * y * one_minus_cos;
    rotation_matrix->data[1][2] = y * z * one_minus_cos - x * sin_theta;

    rotation_matrix->data[2][0] = z * x * one_minus_cos - y * sin_theta;
    rotation_matrix->data[2][1] = z * y * one_minus_cos + x * sin_theta;
    rotation_matrix->data[2][2] = cos_theta + z * z * one_minus_cos;

    return rotation_matrix;
} */
