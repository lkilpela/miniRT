/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:03:14 by jlu               #+#    #+#             */
/*   Updated: 2024/10/08 12:04:02 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

/* CHAINING TRANSFORMATIONS - REVERSE ORDER: TRANSLATION -> SCALING -> ROTATION
** Apply a series of transformations to a shape
*/
void	chaining_transformations(t_shape *shape,
							t_matrix combine_rotations,
							t_matrix scaling_matrix,
							t_matrix
							translation_matrix)											
{
	t_matrix	combined_matrix;
	t_matrix	final_matrix;

	combined_matrix = multiply_matrices(combine_rotations, scaling_matrix);
	final_matrix = multiply_matrices(translation_matrix, combined_matrix);
	shape->transform = final_matrix;
}