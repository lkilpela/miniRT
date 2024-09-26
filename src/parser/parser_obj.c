/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:39:24 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/26 14:43:44 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

void	parse_sphere(char **info, t_world *w)
{
	t_shape	*sp;
	float	diameter;
	float	radius;
	t_tuple	center;
	t_color color;

	if (count_elements(info) != 4)
		fatal_error("Invalid format: Sphere should have 4 elements\n");
	parse_vector(info[1], &center);
	diameter = (double)ft_atof(info[2]);
	radius = diameter / 2;
	parse_color(info[3], &color);
	sp = sphere(center, radius);
	//set_sphere_params(sp, center, radius);
	sp->material->color = color;
	add_object(w, sp);
}

void	parse_plane(char **info, t_world *w)
{
	t_shape *pl;
	t_tuple	point;
	t_tuple	normal;
	t_color	color;

	if (count_elements(info) != 4)
		fatal_error("Invalid format: Plane should have 4 elements\n");
	parse_vector(info[1], &point);
	parse_vector(info[2], &normal);
	normal = normalize(normal);
	parse_color(info[3], &color);
	pl = plane(point, normal);
	pl->material->color = color;
	add_object(w, pl);
}

void	parse_cylinder(char **info, t_world *w)
{
	t_shape		*cy;
	t_tuple		center;
	t_tuple		axis;
	double		radius;
	double		height;
	t_color		color;

	if (count_elements(info) != 6)
		fatal_error("Invalid format: Cylinder should have 6 elements\n");
	parse_vector(info[1], &center);
	parse_vector(info[2], &axis);
	axis = normalize(axis);
	radius = (double)ft_atof(info[3]) / 2;
	height = (double)ft_atof(info[4]);
	parse_color(info[5], &color);
	cy = cylinder(center, axis, radius, height);
	cy->material->color = color;
	add_object(w, cy);
}

void print_sp(t_shape *shape)
{
	t_sphere *sp;

	sp = (t_sphere *)shape->object;
	printf("Sphere:\n");
	printf("Center: %f %f %f\n", sp->center.x, sp->center.y, sp->center.z);
	printf("Radius: %f\n", sp->radius);
}

void print_plane(t_shape *shape)
{
	t_plane *pl;

	pl = (t_plane *)shape->object;
	printf("Plane:\n");
	printf("Point: %f %f %f\n", pl->point.x, pl->point.y, pl->point.z);
	printf("Normal: %f %f %f\n", pl->normal.x, pl->normal.y, pl->normal.z);
}

void print_cylinder(t_shape *shape)
{
	t_cylinder *cy;

	cy = (t_cylinder *)shape->object;
	printf("Cylinder:\n");
	printf("Center: %f %f %f\n", cy->center.x, cy->center.y, cy->center.z);
	printf("Axis: %f %f %f\n", cy->axis.x, cy->axis.y, cy->axis.z);
	printf("Radius: %f\n", cy->radius);
	printf("Height: %f\n", cy->height);
}

void print_objects(t_shape *object, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		if (object[i].id == SPHERE)
			print_sp(&object[i]);
		else if (object[i].id == PLANE)
			print_plane(&object[i]);
		else if (object[i].id == CYLINDER)
			print_cylinder(&object[i]);
		i++;
	}
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
	print_objects(w->object, w->count);
}
