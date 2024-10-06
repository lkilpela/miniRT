/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:57:35 by jlu               #+#    #+#             */
/*   Updated: 2024/10/06 12:59:04 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

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

	if (!m)
		return (0);
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
