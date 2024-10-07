/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:41:46 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/07 14:44:07 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

void	parse_color(char *str, t_color *color)
{
	char	**components;
	int i;

	components = ft_split(str, ',');
	if (!components || !components[0] || !components[1] || !components[2])
		fatal_error("Invalid format\n");
	i = 0;
	while (components[i])
	{
		if (!is_valid_float(components[i]))
			fatal_error("Invalid color component\n");
		i++;
	}
	color->r = ft_atof(components[0]);
	color->g = ft_atof(components[1]);
	color->b = ft_atof(components[2]);
	if (!is_valid_color_range(color->r) 
		|| !is_valid_color_range(color->g)
		|| !is_valid_color_range(color->b)) 
	{
		fatal_error("Color component out of range (0-255)\n");
	}
	*color = normalize_color(*color);
	ft_free(components);
}

void	parse_point(char *str, t_tuple *p)
{
	char	**axis;

	axis = ft_split(str, ',');
	if (!axis || !axis[0] || !axis[1] || !axis[2])
		fatal_error("Invalid format\n");
	validate_tuple(axis);
	p->x = (double)ft_atof(axis[0]);
	p->y = (double)ft_atof(axis[1]);
	p->z = (double)ft_atof(axis[2]);
	p->w = 1;
	ft_free(axis);
}

void	parse_vector(char *str, t_tuple *v)
{
	char	**axis;

	axis = ft_split(str, ',');
	if (!axis || !axis[0] || !axis[1] || !axis[2])
		fatal_error("Invalid format\n");
	validate_tuple(axis);
	v->x = (double)ft_atof(axis[0]);
	v->y = (double)ft_atof(axis[1]);
	v->z = (double)ft_atof(axis[2]);
	v->w = 0;
	ft_free(axis);
}

void	space_replace(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\t' || s[i] == '\v' || s[i] == '\f' 
			|| s[i] == '\r' || s[i] == '\n')
			s[i] = ' ';
		i++;
	}
}
