/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:41:46 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/07 14:41:00 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Function to count the number of elements in the array
int count_elements(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i] != NULL)
		i++;
	return (i);
}

bool	is_valid_normal(t_tuple *normal)
{
	if (normal->x < -1 || normal->x > 1)
		return (false);
	if (normal->y < -1 || normal->y > 1)
		return (false);
	if (normal->z < -1 || normal->z > 1)
		return (false);
	return (true);
}

bool	is_valid_color_range(float value)
{
	return (value >= 0.0f && value <= 255.0f);
}
