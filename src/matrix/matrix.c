/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:19:53 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/01 09:54:42 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

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
	if (!m->data)
    {
        free(m);
        return NULL;
    }
    int i = 0;
    while (i < y)
    {
        m->data[i] = calloc(x, sizeof(float));
        if (!m->data[i]) {
            for (int j = 0; j < i; j++) {
                free(m->data[j]);
            }
            free(m->data);
            free(m);
            return NULL;
        }
        i++;
    }
    return m;
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
	if (!matrix)
		fatal_error("get_matrix_element: Matrix is NULL\n");
	if (row >= matrix->y || col >= matrix->x)
		fatal_error("get_matrix_element: Index out of bounds\n");
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
	i = 0;
	while (i < size)
	{
		m->data[i][i] = 1.0;
		i++;
	}
	return (m);
}
