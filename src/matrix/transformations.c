/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:09:48 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/07 13:31:20 by lkilpela         ###   ########.fr       */
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
	m->data[0][3] = x;
	m->data[1][3] = y;
	m->data[2][3] = z;
	return (m);
}

/* SCALING - RESIZING AN OBJECT
*/
t_matrix	scaling(float x, float y, float z)
{
	t_matrix	m;

	m = identity_matrix();
	m->data[0][0] = x;
	m->data[1][1] = y;
	m->data[2][2] = z;
	return (m);
}

/* DEFINING VIEW TRANSFORMATION 
** Pretends the eye moves instead of the world
** - Specify where you want the eye to be in the scene (from)
** - Specify where you want the eye to look at (to)
** - Specify the direction of the up vector (up)
** - Return a view transformation matrix
*/
t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple		forward;
	t_tuple		left;
	t_tuple		true_up;
	t_matrix	*orientation;

	forward = normalize(subtract(to, from));
	left = cross(forward, normalize(up));
	true_up = cross(left, forward);
	orientation = identity_matrix();
	orientation.data[0][0] = left.x;
	orientation.data[0][1] = left.y;
	orientation.data[0][2] = left.z;
	orientation.data[1][0] = true_up.x;
	orientation.data[1][1] = true_up.y;
	orientation.data[1][2] = true_up.z;
	orientation.data[2][0] = -forward.x;
	orientation.data[2][1] = -forward.y;
	orientation.data[2][2] = -forward.z;
	return (multiply_matrices(orientation,
			translation(-from.x, -from.y, -from.z)));
}

/* ROTATION_AROUND_AXIS */
t_matrix	rotation(t_tuple axis)
{
	t_matrix	rotation_matrix;

	t_tuple u = vector(0, 1, 0);
	float angle = acos(dot(u, axis));
	t_tuple a = cross(u, axis);

	float c = cos(angle);
	float s = sin(angle);
	float t = 1 - c;

	rotation_matrix = identity_matrix();
	rotation_matrix.data[0][0] = c + a.x * a.x * t;
	rotation_matrix.data[0][1] = a.x * a.y * t - a.z * s;
	rotation_matrix.data[0][2] = a.x * a.z * t + a.y * s;
	rotation_matrix.data[1][0] = a.x * a.y * t + a.z * s;
	rotation_matrix.data[1][1] = c + a.y * a.y * t;
	rotation_matrix.data[1][2] = a.y * a.z * t - a.x * s;
	rotation_matrix.data[2][0] = a.x * a.z * t - a.y * s;
	rotation_matrix.data[2][1] = a.y * a.z * t + a.x * s;
	rotation_matrix.data[2][2] = c + a.z * a.z * t;
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
