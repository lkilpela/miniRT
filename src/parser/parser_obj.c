/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:39:24 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/25 17:42:53 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

void	parse_sphere(char **info, t_world *w)
{
	t_tuple	center;
	float	diameter;
	float	radius;
	t_color	color;

	if (count_elements(info) != 4)
		fatal_error("Invalid format: Sphere should have 4 elements\n");
	parse_vector(info[1], center);
	diameter = (double)ft_atof(info[2]);
	radius = diameter / 2;
	parse_color(info[3], color);
	add_object(w, create_sphere(center, radius, color));
}

void	parse_plane(char **info, t_world *w)
{
	t_tuple	point;
	t_tuple	normal;
	t_color	color;

	if (count_elements(info) != 4)
		fatal_error("Invalid format: Plane should have 4 elements\n");
	parse_vector(info[1], point);
	parse_vector(info[2], normal);
	normal = normalize(normal);
	parse_color(info[3], color);
	add_object(w, create_plane(point, normal, color));
}

void	parse_cylinder(char **info, t_world *w)
{
	t_tuple		center;
	t_tuple		axis;
	double		radius;
	double		height;
	t_color		color;

	if (count_elements(info) != 6)
		fatal_error("Invalid format: Cylinder should have 6 elements\n");
	parse_vector(info[1], center);
	parse_vector(info[2], axis);
	axis = normalize(axis);
	radius = (double)ft_atof(info[3]);
	height = (double)ft_atof(info[4]);
	parse_color(info[5], color);
	add_object(w, create_cylinder(center, axis, radius, height, color));
}

void	add_object(t_world *w, t_shape *object)
{
	t_shape	*temp;
	int			i;

	i = 0;
	temp = calloc(1, sizeof(t_shape) * (w->count + 1));
	if (temp == NULL)
		return ;
	while (i < w->count)
	{
		temp[i] = w->object[i];
		i++;
	}
	temp[w->count] = *object;
	free(w->object);
	w->object = temp;
	w->count++;
}
