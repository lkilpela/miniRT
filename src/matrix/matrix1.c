/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:27:23 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/09 00:23:22 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

static float	determinant(t_matrix m);

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
static float	minor(t_matrix a, int y, int x)
{
	t_matrix	sub;
	float		det;

	sub = submatrix(a, y, x);
	det = determinant(sub);
	return (det);
}

/* COMPUTING COFACTORS
** Compute the minor at a given row and column.
** if row + col is even, the cofactor is the minor.
** if row + col is odd, the cofactor is the negative of the minor.
*/
static float	cofactor(t_matrix a, int y, int x)
{
	float	minor_value;

	minor_value = minor(a, y, x);
	if ((y + x) % 2 != 0)
		return (-minor_value);
	return (minor_value);
}

/* INVERTING 2x2 MATRICES
** determinant = ad - bc 
** If determinant is 0, the matrix is not invertible (no solution)
*/
static float	determinant_2x2(t_matrix a)
{
	if (a.x != 2 || a.y != 2)
		fatal_error("Matrix is not 2x2\n");
	return (a.data[0][0] * a.data[1][1] - a.data[0][1] * a.data[1][0]);
}

/* COMPUTING DETERMINANTS FOR LARGER MATRICES
** The determinant of a 2x2 matrix is ad - bc.
** Multiplying the element by its cofactor and add the results.
*/
static float	determinant(t_matrix m)
{
	float	det;
	int		x;

	if (m.x != m.y)
		fatal_error("Matrix is not square\n");
	if (m.x == 2)
		return (determinant_2x2(m));
	det = 0;
	x = 0;
	while (x < m.x)
	{
		det += m.data[0][x] * cofactor(m, 0, x);
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
t_matrix	inverse(t_matrix m)
{
	t_idx		cnt;
	t_matrix	m2;
	float		det;
	float		c;

	det = determinant(m);
	if (float_equals(det, 0.0, 0.001))
		fatal_error("Matrix is not invertible\n");
	m2 = identity_matrix();
	cnt.i = 0;
	while (cnt.i < m.y)
	{
		cnt.j = 0;
		while (cnt.j < m.x)
		{
			c = cofactor(m, cnt.i, cnt.j);
			m2.data[cnt.j][cnt.i] = c / det;
			cnt.j++;
		}
		cnt.i++;
	}
	return (m2);
}
