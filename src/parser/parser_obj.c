/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:39:24 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/08 12:37:53 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

void	parse_sphere(char **info, t_world *w)
{
	t_shape	*sp;
	float	diameter;
	float	radius;
	t_tuple	center;
	t_color	color;

	if (count_elements(info) != 4)
		fatal_error("Invalid format: Sphere should have 4 elements\n");
	parse_point(info[1], &center);
	diameter = (double)ft_atof(info[2]);
	radius = diameter / 2;
	if (radius < 0)
		fatal_error("Sphere radius invalid\n");
	parse_color(info[3], &color);
	sp = sphere(center, radius);
	sp->material->color = color;
	add_object(w, sp);
}

void	parse_plane(char **info, t_world *w)
{
	t_shape	*pl;
	t_tuple	point;
	t_tuple	normal;
	t_color	color;

	if (count_elements(info) != 4)
		fatal_error("Invalid format: Plane should have 4 elements\n");
	parse_point(info[1], &point);
	parse_vector(info[2], &normal);
	if (!is_valid_normal(&normal))
		fatal_error("Invalid format: Plane normal range\n");
	normal = normalize(normal);
	parse_color(info[3], &color);
	pl = plane(point, normal);
	pl->material->color = color;
	add_object(w, pl);
}

// double data[2] data[0] = radius and data[1] = height
void	parse_cylinder(char **info, t_world *w)
{
	t_shape		*cy;
	t_tuple		center;
	t_tuple		axis;
	double		data[2];
	t_color		color;

	if (count_elements(info) != 6)
		fatal_error("Invalid format: Cylinder should have 6 elements\n");
	parse_point(info[1], &center);
	parse_vector(info[2], &axis);
	if (!is_valid_normal(&axis))
		fatal_error("Invalid format: Cylinder axis range\n");
	axis = normalize(axis);
	data[0] = (double)ft_atof(info[3]) / 2;
	if (data[0] < 0)
		fatal_error("Cylinder radius invalid\n");
	data[1] = (double)ft_atof(info[4]);
	if (data[1] < 0)
		fatal_error("Cylinder height invalid\n");
	parse_color(info[5], &color);
	cy = cylinder(center, axis, data[0], data[1]);
	cy->material->color = color;
	add_object(w, cy);
}

void	add_object(t_world *w, t_shape *object)
{
	t_shape	**temp;
	int		i;

	i = 0;
	temp = calloc(1, sizeof(t_shape *) * (w->count + 1));
	if (temp == NULL)
		return ;
	while (i < w->count)
	{
		temp[i] = w->objects[i];
		i++;
	}
	temp[w->count] = object;
	free(w->objects);
	w->objects = temp;
	w->count++;
}
