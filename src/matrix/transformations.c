/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:09:48 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/09 15:23:32 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

/* TRANSLATION - MOVING AN OBJECT
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
t_matrix	translation(float x, float y, float z)
{
	t_matrix	m;

	m = identity_matrix();
	m.data[0][3] = x;
	m.data[1][3] = y;
	m.data[2][3] = z;
	return (m);
}

/* SCALING - RESIZING AN OBJECT
*/
t_matrix	scaling(float x, float y, float z)
{
	t_matrix	m;

	m = identity_matrix();
	m.data[0][0] = x;
	m.data[1][1] = y;
	m.data[2][2] = z;
	return (m);
}

/* Helper function to calculate rotation matrix elements */
static void	calculate_rotation_formula(float angle, t_tuple a,
						t_matrix *rotation_matrix)
{
	float	c;
	float	s;
	float	t;

	c = cos(angle);
	s = sin(angle);
	t = 1 - c;
	rotation_matrix->data[0][0] = c + a.x * a.x * t;
	rotation_matrix->data[0][1] = a.x * a.y * t - a.z * s;
	rotation_matrix->data[0][2] = a.x * a.z * t + a.y * s;
	rotation_matrix->data[1][0] = a.x * a.y * t + a.z * s;
	rotation_matrix->data[1][1] = c + a.y * a.y * t;
	rotation_matrix->data[1][2] = a.y * a.z * t - a.x * s;
	rotation_matrix->data[2][0] = a.x * a.z * t - a.y * s;
	rotation_matrix->data[2][1] = a.y * a.z * t + a.x * s;
	rotation_matrix->data[2][2] = c + a.z * a.z * t;
}

/* ROTATION_AROUND_AXIS */
t_matrix	rotation(t_tuple axis, t_tuple u)
{
	t_matrix	rotation_matrix;
	float		angle;
	t_tuple		a;

	angle = acos(dot(u, axis));
	a = cross(u, axis);
	rotation_matrix = identity_matrix();
	calculate_rotation_formula(angle, a, &rotation_matrix);
	return (rotation_matrix);
}

/* CHAINING TRANSFORMATIONS - REVERSE ORDER: TRANSLATION -> SCALING -> ROTATION
** Apply a series of transformations to a shape
*/
void	chaining_transformations(t_shape *shape,
							t_matrix combine_rotations,
							t_matrix scaling_matrix,
							t_matrix translation_matrix)
{
	t_matrix	combined_matrix;
	t_matrix	final_matrix;

	combined_matrix = multiply_matrices(combine_rotations, scaling_matrix);
	final_matrix = multiply_matrices(translation_matrix, combined_matrix);
	shape->transform = final_matrix;
}
