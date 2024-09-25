/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:39:24 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/17 08:43:55 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "world.h"
#include "error.h"

void	parse_sphere(char **info, t_world *w)
{
	t_vec3	center;
	double	diameter;
	double	radius;
	t_color	color;

	if (count_elements(info) != 4)
		fatal_error("Invalid format: Sphere should have 4 elements\n");
	parse_vector(info[1], &center);
	diameter = (double)ft_atof(info[2]);
	radius = diameter / 2;
	parse_color(info[3], &color);
	add_object(w, create_sphere(center, radius, color));
}

void	parse_plane(char **info, t_world *w)
{
	t_vec3	point;
	t_vec3	normal;
	t_color	color;

	if (count_elements(info) != 4)
		fatal_error("Invalid format: Plane should have 4 elements\n");
	parse_vector(info[1], &point);
	parse_vector(info[2], &normal);
	normal = vec3_normalize(normal);
	parse_color(info[3], &color);
	add_object(w, create_plane(point, normal, color));
}

void	parse_cylinder(char **info, t_world *w)
{
	t_vec3		center;
	t_vec3		axis;
	double		radius;
	double		height;
	t_color		color;

	if (count_elements(info) != 6)
		fatal_error("Invalid format: Cylinder should have 6 elements\n");
	parse_vector(info[1], &center);
	parse_vector(info[2], &axis);
	axis = vec3_normalize(axis);
	radius = (double)ft_atof(info[3]);
	height = (double)ft_atof(info[4]);
	parse_color(info[5], &color);
	add_object(w, create_cylinder(center, axis, radius, height, color));
}
