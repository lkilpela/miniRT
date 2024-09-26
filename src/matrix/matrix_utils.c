/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:43:27 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/26 09:50:57 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

// Function to check if matrix allocation failed
void	*check_memory_fail(void *ptr, t_matrix *m)
{
	if (!ptr)
	{
		destroy_matrix(m);
		return (NULL);
	}
	return (ptr);
}

// Function to deallocate memory for the matrix
void	destroy_matrix(t_matrix *m)
{
	if (m)
	{
		free(m->data[0]);
		free(m->data);
		free(m);
	}
}
