/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:41:46 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/07 14:54:12 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Function to count the number of elements in the array
int	count_elements(char **array)
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

bool	is_valid_float(const char *str)
{
	int		i;
	int		count;
	bool	has_digits;

	i = 0;
	count = 0;
	has_digits = false;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			has_digits = true;
		else if (str[i] == '.')
		{
			if (count++ > 0)
				return (false);
		}
		else
			return (false);
		i++;
	}
	return (has_digits);
}

void	validate_tuple(char **str)
{
	int	i;

	i = 0;
	if (!str)
		fatal_error("Null pointer provided for tuple\n");
	while (str[i])
	{
		if (!is_valid_float(str[i]))
			fatal_error("Invalid float number\n");
		i++;
	}
	if (i != 3)
		fatal_error("Invalid number of tuple\n");
}
