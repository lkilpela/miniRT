/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:19:53 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/07 10:07:40 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Function to create a matrix
t_matrix	create_matrix(int x, int y)
{
	t_matrix	m;
	int			i;
	int			j;

	m.x = x;
	m.y = y;
	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			m.data[i][j] = 0;
			j++;
		}
		i++;
	}
	return (m);
}

// Function to get the value of a matrix element
float	get_matrix_element(t_matrix matrix, int row, int col)
{
/* 	if (!matrix)
		fatal_error("get_matrix_element: Matrix is NULL\n"); */
	if (row >= matrix.y || col >= matrix.x)
		fatal_error("get_matrix_element: Index out of bounds\n");
	return (matrix.data[row][col]);
}

/* Function to init a matrix with 1.0 on the diagonal and 0.0 elsewhere
identity =
1 0 0 0
0 1 0 0
0 0 1 0
0 0 0 1
*/
t_matrix	identity_matrix()
{
	t_matrix	m;
	int			i;

	i = 0;
	m = create_matrix(4, 4);
	while (i < 4)
	{
		m.data[i][i] = 1.0;
		i++;
	}
	return (m);
}
