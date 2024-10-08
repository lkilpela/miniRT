/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:19:53 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/09 00:14:57 by lkilpela         ###   ########.fr       */
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
t_matrix	identity_matrix(void)
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

/* TRANSPOSING MATRICES
** Transposing a matrix means to switch its rows and columns.
** For example, the transpose of the following matrix:
** 1 2 3
** 4 5 6
** is:
** 1 4
** 2 5
** 3 6
*/
t_matrix	transpose_matrix(t_matrix a)
{
	t_matrix	t;
	int			i;
	int			j;

	t = identity_matrix();
	i = 0;
	while (i < a.y)
	{
		j = 0;
		while (j < a.x)
		{
			t.data[j][i] = a.data[i][j];
			j++;
		}
		i++;
	}
	return (t);
}

/* SUBMATRICES
** A submatrix is a matrix that is derived from another matrix by removing
one or more of its rows and/or columns.
** For example, the submatrix of the following matrix, removing the first 
row and the last column:
** 1 2 3 <- Remove this row
** 4 5 6
** 7 8 9
**     ^ Remove this column
** is:
** 4 5
** 7 8
** To find the submatrix, we remove the row and column specified by the 
arguments.
*/
t_matrix	submatrix(t_matrix a, int y, int x)
{
	t_matrix	sub;
	t_idx		cnt;

	sub = create_matrix(a.x - 1, a.y - 1);
	cnt.j = 0;
	cnt.i = -1;
	while (++cnt.i < a.y)
	{
		if (cnt.i == y)
			continue ;
		cnt.k = -1;
		cnt.l = 0;
		while (++cnt.k < a.x)
		{
			if (cnt.k == x)
				continue ;
			sub.data[cnt.j][cnt.l++] = a.data[cnt.i][cnt.k];
		}
		cnt.j++;
	}
	return (sub);
}
