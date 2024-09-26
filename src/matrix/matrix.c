/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:19:53 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/26 09:50:16 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

// Function to allocate memory for the matrix
t_matrix	*allocate_matrix(int y, int x)
{
	t_matrix	*m;
	int			i;

	m = calloc(1, sizeof(t_matrix));
	if (!m)
		return (NULL);
	m->x = x;
	m->y = y;
	m->data = check_memory_fail(calloc(y, sizeof(float *)), m);
	if (!m->data)
		return (NULL);
	m->data[0] = check_memory_fail(calloc(y * x, sizeof(float)), m);
	if (!m->data[0])
		return (NULL);
	i = 1;
	while (i < y)
	{
		m->data[i] = m->data[0] + i * x;
		i++;
	}
	return (m);
}

// Function to create a matrix
t_matrix	*create_matrix(int x, int y, float values[y][x])
{
	t_matrix	*m;
	int			i;
	int			j;

	m = allocate_matrix(y, x);
	if (!m)
		return (NULL);
	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			m->data[i][j] = values[i][j];
			j++;
		}
		i++;
	}
	return (m);
}

// Function to get the value of a matrix element
float	get_matrix_element(t_matrix *matrix, int row, int col)
{
	return (matrix->data[row][col]);
}

/* Function to init a matrix with 1.0 on the diagonal and 0.0 elsewhere
identity =
1 0 0 0
0 1 0 0
0 0 1 0
0 0 0 1
*/
t_matrix	*identity_matrix(int size)
{
	t_matrix	*m;
	int			i;

	m = allocate_matrix(size, size);
	if (!m)
		return (NULL);
	while (i < size)
	{
		m->data[i][i] = 1.0;
		i++;
	}
	return (m);
}