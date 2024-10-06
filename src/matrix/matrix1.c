/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:27:23 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/06 12:59:11 by jlu              ###   ########.fr       */
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
	t_idx		cnt;

	sub = allocate_matrix(a->y - 1, a->x - 1);
	if (!sub)
		return (NULL);
	cnt.j = 0; //sub_i
	cnt.i = -1; // i
	while (++cnt.i < a->y)
	{
		if (cnt.i == y)
			continue ;
		cnt.k = -1; //j
		cnt.l = 0; //sub_j
		while (++cnt.k < a->x)
		{
			if (cnt.k == x)
				continue ;
			sub->data[cnt.j][cnt.l++] = a->data[cnt.i][cnt.k];
		}
		cnt.j++;
	}
	return (sub);
}

// t_matrix	*submatrix(t_matrix *a, int y, int x)
// {
// 	t_matrix	*sub;
// 	int			sub_i;
// 	int			sub_j;
// 	int			i;
// 	int			j;

// 	sub = allocate_matrix(a->y - 1, a->x - 1);
// 	if (!sub)
// 		return (NULL);
// 	sub_i = 0;
// 	i = 0;
// 	while (i < a->y)
// 	{
// 		if (i == y)
// 		{
// 			i++;
// 			continue ;
// 		}
// 		j = 0;
// 		sub_j = 0;
// 		while (j < a->x)
// 		{
// 			if (j == x)
// 			{
// 				j++;
// 				continue ;
// 			}
// 			sub->data[sub_i][sub_j] = a->data[i][j];
// 			sub_j++;
// 			j++;
// 		}
// 		sub_i++;
// 		i++;
// 	}
// 	return (sub);
// }

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
/* t_matrix	*inverse(t_matrix *m)
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
} */

t_matrix* inverse(t_matrix *m)
{
    float det = determinant(m);
    if (float_equals(det, 0.0, 0.001)) {
        fprintf(stderr, "Matrix is not invertible\n");
        return NULL; // or handle error appropriately
    }

    t_matrix *m2 = allocate_matrix(m->y, m->x);
    if (!m2)
        return NULL;

    for (int row = 0; row < m->y; row++) {
        for (int col = 0; col < m->x; col++) {
            float c = cofactor(m, row, col);
            m2->data[col][row] = c / det; // Note the transpose operation
        }
    }
    return m2;
}
