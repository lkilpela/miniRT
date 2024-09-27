/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:27:23 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/27 10:43:47 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

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
t_matrix	*transpose_matrix(t_matrix *a)
{
	t_matrix	*t;
	int			i;
	int			j;

	t = allocate_matrix(a->x, a->y);
	if (!t)
		return (NULL);
	i = 0;
	while (i < a->y)
	{
		j = 0;
		while (j < a->x)
		{
			t->data[j][i] = a->data[i][j];
			j++;
		}
		i++;
	}
	return (t);
}

/* INVERTING 2x2 MATRICES
** determinant = ad - bc 
** If determinant is 0, the matrix is not invertible (no solution)
*/
float	determinant_2x2(t_matrix *a)
{
	if (a->x != 2 || a->y != 2)
	{
		ft_putstr_fd("Matrix is not 2x2\n", STDERR_FILENO);
		return (0);
	}
	return (a->data[0][0] * a->data[1][1] - a->data[0][1] * a->data[1][0]);
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
t_matrix	*submatrix(t_matrix *a, int y, int x)
{
	t_matrix	*sub;
	int			sub_i;
	int			sub_j;
	int			i;
	int			j;

	sub = allocate_matrix(a->y - 1, a->x - 1);
	if (!sub)
		return (NULL);
	sub_i = 0;
	i = 0;
	while (i < a->y)
	{
		if (i == y)
		{
			i++;
			continue ;
		}
		j = 0;
		sub_j = 0;
		while (j < a->x)
		{
			if (j == x)
			{
				j++;
				continue ;
			}
			sub->data[sub_i][sub_j] = a->data[i][j];
			sub_j++;
			j++;
		}
		sub_i++;
		i++;
	}
	return (sub);
}

/* MANIPULATING MINORS
** A minor is the determinant of the submatrix that results from removing 
the i-th row and j-th column of a matrix.
** For example, the minor of the following matrix, removing the first row 
and the last column:
** 1 2 3 <- Remove this row
** 4 5 6
** 7 8 9
**     ^ Remove this column
** is:
** 5 6
** 8 9
** To find the minor, we first find the submatrix, then calculate 
the determinant of the submatrix.
*/
float	minor(t_matrix *a, int y, int x)
{
	t_matrix	*sub;
	float		det;

	sub = submatrix(a, y, x);
	det = determinant(sub);
	destroy_matrix(sub);
	return (det);
}

/* COMPUTING COFACTORS
** Compute the minor at a given row and column.
** if row + col is even, the cofactor is the minor.
** if row + col is odd, the cofactor is the negative of the minor.
*/
float	cofactor(t_matrix *a, int y, int x)
{
	float	minor_value;

	minor_value = minor(a, y, x);
	if ((y + x) % 2 != 0)
		return (-minor_value);
	return (minor_value);
}

/* COMPUTING DETERMINANTS FOR LARGER MATRICES
** The determinant of a 2x2 matrix is ad - bc.
** Multiplying the element by its cofactor and add the results.
*/
float	determinant(t_matrix *m)
{
	float	det;
	int		x;

	if (m->x != m->y)
	{
		ft_putstr_fd("Matrix is not square\n", STDERR_FILENO);
		return (0);
	}
	if (m->x == 2)
		return (determinant_2x2(m));
	det = 0;
	x = 0;
	while (x < m->x)
	{
		det += m->data[0][x] * cofactor(m, 0, x);
		x++;
	}
	return (det);
}

/* INVERTING MATRICES
** The inverse of a matrix A is denoted A^-1.
** The inverse of a matrix is the matrix that, when multiplied with
the original matrix, gives the identity matrix.
** The inverse of a matrix is calculated by:
** 1. Calculating the determinant of the matrix.
** 2. Calculating the matrix of cofactors.
** 3. Transposing the matrix of cofactors.
** 4. Dividing the transposed matrix of cofactors by the determinant.
** 
*/
t_matrix	*inverse(t_matrix *m)
{
	float		det;
	t_matrix	*m2;
	int			x;
	int			y;
	float		c;

	if (!m)
		return (NULL);
	if (m->x != m->y)
	{
		ft_putstr_fd("Matrix is not square\n", STDERR_FILENO);
		return (NULL);
	}
	det = determinant(m);
	if (float_equals(det, 0.0, 0.001))
	{
		ft_putstr_fd("Matrix is not invertible\n", STDERR_FILENO);
		return (NULL);
	}
	m2 = allocate_matrix(m->y, m->x);
	if (!m2)
		return (NULL);
	y = 0;
	while (y < m->y)
	{
		x = 0;
		while (x < m->x)
		{
			c = cofactor(m, y, x);
			m2->data[y][x] = c / det;
			x++;
		}
		y++;
	}
	return (m2);
}
