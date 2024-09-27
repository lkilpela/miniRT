/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:56:05 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/26 19:38:22 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

t_tuple	matrix_multiply_tuple(t_matrix *m, t_tuple t)
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
	
	    // Debugging output
/*     printf("Matrix:\n");
    print_matrix(m); */
    printf("Tuple:\n");
    print_tuple(t);
/*     printf("Result:\n");
    print_tuple(result);
	 */
	return (result);
}

t_matrix	*multiply_matrices(t_matrix *a, t_matrix *b)
{
	t_matrix	*m;
	int			i;
	int			j;
	int			k;

	if (a->x != b->y)
	{
		ft_putstr_fd("Matrices can not be multiplied\n", STDERR_FILENO);
		return (NULL);
	}
	m = allocate_matrix(a->y, b->x);
	if (!m)
		return (NULL);
	i = 0;
	while (i < a->y)
	{
		j = 0;
		while (j < b->x)
		{
			k = 0;
			while (k < a->x)
			{
				m->data[i][j] += a->data[i][k] * b->data[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (m);
}

/* // Function to check if two matrices are equal
bool matrices_are_equal(t_matrix *a, t_matrix *b)
{
	if (a == NULL || b == NULL) {
		return false;
	}
	if (a->x != b->x || a->y != b->y) {
		return false;
	}
	for (int i = 0; i < a->y; i++) {
		for (int j = 0; j < a->x; j++) {
			if (!float_equals(a->data[i][j], b->data[i][j], EPSILON))
				return false;
		}
	}
	return (true);
} */
