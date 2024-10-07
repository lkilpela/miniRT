/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:56:05 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/07 14:59:03 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

t_tuple	matrix_multiply_tuple(t_matrix m, t_tuple t)
{
	t_tuple	result;

	result.x = get_matrix_element(m, 0, 0) * t.x
		+ get_matrix_element(m, 0, 1) * t.y
		+ get_matrix_element(m, 0, 2) * t.z
		+ get_matrix_element(m, 0, 3) * t.w;
	result.y = get_matrix_element(m, 1, 0) * t.x
		+ get_matrix_element(m, 1, 1) * t.y
		+ get_matrix_element(m, 1, 2) * t.z
		+ get_matrix_element(m, 1, 3) * t.w;
	result.z = get_matrix_element(m, 2, 0) * t.x
		+ get_matrix_element(m, 2, 1) * t.y
		+ get_matrix_element(m, 2, 2) * t.z
		+ get_matrix_element(m, 2, 3) * t.w;
	result.w = get_matrix_element(m, 3, 0) * t.x
		+ get_matrix_element(m, 3, 1) * t.y
		+ get_matrix_element(m, 3, 2) * t.z
		+ get_matrix_element(m, 3, 3) * t.w;
	return (result);
}

t_matrix	multiply_matrices(t_matrix a, t_matrix b)
{
	t_matrix	m;
	t_idx		c;

	m = create_matrix(b.x, a.y);
	if (a.x != b.y)
		fatal_error("Matrices can not be multiplied\n");
	c.i = 0;
	while (c.i < a.y)
	{
		c.j = 0;
		while (c.j < b.x)
		{
			c.k = 0;
			while (c.k < a.x)
			{
				m.data[c.i][c.j] += a.data[c.i][c.k] * b.data[c.k][c.j];
				c.k++;
			}
			c.j++;
		}
		c.i++;
	}
	return (m);
}

// Function to compare two floating-point numbers with a tolerance
bool	float_equals(float a, float b, float epsilon)
{
	return (fabs(a - b) < epsilon);
}
