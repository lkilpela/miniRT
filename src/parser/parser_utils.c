/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:41:46 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/27 08:52:00 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Converting RGB values from the range [0, 255] to [0.0, 1.0]
// by dividing by 255.0.
t_color	normalize_color(t_color color)
{
	color.r /= 255.0f;
	color.g /= 255.0f;
	color.b /= 255.0f;
	return (color);
}

void	parse_color(char *str, t_color *color)
{
	char	**components;

	components = ft_split(str, ',');
	if (!components || !components[0] || !components[1] || !components[2])
		fatal_error("Invalid format\n");
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
	validate_vector(axis);
	p->x = (double)ft_atof(axis[0]);
	p->y = (double)ft_atof(axis[1]);
	p->z = (double)ft_atof(axis[2]);
	point(p->x, p->y, p->z);
	ft_free(axis);
}

void	parse_vector(char *str, t_tuple *v)
{
	char	**axis;

	axis = ft_split(str, ',');
	if (!axis || !axis[0] || !axis[1] || !axis[2])
		fatal_error("Invalid format\n");
	validate_vector(axis);
	v->x = (double)ft_atof(axis[0]);
	v->y = (double)ft_atof(axis[1]);
	v->z = (double)ft_atof(axis[2]);
	vector(v->x, v->y, v->z);
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

int	is_valid_identifier(t_id id)
{
	return (id == AMBIENT || id == CAMERA || id == LIGHT
		|| id == SPHERE || id == PLANE || id == CYLINDER);
}
