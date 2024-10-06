/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:43:27 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/05 17:30:33 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

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
		if (m->data)
        {
            if (m->data[0])
                free(m->data[0]);
            free(m->data);
        }
        free(m);
	}
}

void	free_matrices(t_matrix *a, int i)
{
	while (--i >= 0)
		free(a->data[i]);
	free(a->data);
	free(a);
}

