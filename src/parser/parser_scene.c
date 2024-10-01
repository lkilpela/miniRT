/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:46:52 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/01 09:50:09 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

void	parse_ambient(char **info, t_world *w)
{
	float	ratio;
	t_color	color;	

	if (w->ambient.flag == false)
	{
		if (count_elements(info) != 3)
			fatal_error("Invalid format: Ambient should have 3 elements\n");
		ratio = ft_atof(info[1]);
		if (ratio < 0 || ratio > 1)
			fatal_error("Ambient light ratio out of range (0-1)\n");
		parse_color(info[2], &color);
		w->ambient.ratio = ratio;
		w->ambient.color = color;
		w->ambient.flag = true;
	}
	else
		fatal_error("Ambient light already defined\n");
}

void	parse_camera(char **info, t_world *w)
{
	t_tuple		from;
	t_tuple		orientation_vector;
	double		fov;

	if (w->camera.flag == false)
	{
		if (count_elements(info) != 4)
			fatal_error("Invalid format: Camera should have 4 elements\n");
		parse_point(info[1], &from);
		parse_vector(info[2], &orientation_vector);
		fov = (double)ft_atof(info[3]);
		if (fov < 0 || fov > 180)
			fatal_error("Camera field of view out of range (0-180)\n");
		w->camera = camera(w->window.width, w->window.height, fov);
		w->camera.from = from;
		w->camera.to = orientation_vector; //add(from, orientation_vector);
		w->camera.up = vector(0, 1, 0);
		w->camera.fov = fov;
		w->camera.flag = true;
		setup_camera(&(w->camera));	
	}
	else
		fatal_error("Camera already defined\n");
}

void	parse_light(char **info, t_world *w)
{
	t_tuple	position;
	t_color	color;
	float	brightness;

	if (w->light.flag == false)
	{
		if (count_elements(info) != 4)
			fatal_error("Invalid format: Light should have 4 elements\n");
		parse_point(info[1], &position);
		brightness = ft_atof(info[2]);
		if (brightness < 0 || brightness > 1)
			fatal_error("Light brightness out of range (0-1)\n");
		parse_color(info[3], &color);
		w->light.position = position;
		w->light.brightness = brightness;
		w->light.intensity = color;
		w->light.flag = true;
	}
	else
		fatal_error("Light already defined\n");
}

t_id	get_identifier(char *str)
{
	if (ft_strcmp(str, "A") == 0)
		return (AMBIENT);
	else if (ft_strcmp(str, "C") == 0)
		return (CAMERA);
	else if (ft_strcmp(str, "L") == 0)
		return (LIGHT);
	else if (ft_strcmp(str, "sp") == 0)
		return (SPHERE);
	else if (ft_strcmp(str, "pl") == 0)
		return (PLANE);
	else if (ft_strcmp(str, "cy") == 0)
		return (CYLINDER);
	else
		return (UNKNOWN);
}

void	parser_sort(char **info, t_world *w)
{
	t_id	id;

	id = get_identifier(info[0]);
	if (!is_valid_identifier(id))
		fatal_error("Invalid identifier\n");
	if (id == AMBIENT)
		parse_ambient(info, w);
	else if (id == CAMERA)
		parse_camera(info, w);
	else if (id == LIGHT)
		parse_light(info, w);
	else if (id == SPHERE)
		parse_sphere(info, w);
	else if (id == PLANE)
		parse_plane(info, w);
	else if (id == CYLINDER)
		parse_cylinder(info, w);
	else
		fatal_error("Unknown Scene\n");
}


void	parse_scene(char *filename, t_world *w)
{
	int		fd;
	char	*line;
	char	**info;

	fd = check_open_file(filename);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\0' && line[0] != '\n' && line[0] != '#')
		{
			space_replace(line);
			info = ft_split(line, ' ');
			if (info)
			{
				//print_parsed_info(info); // Debug print for parsed info
				parser_sort(info, w);
				ft_free(info);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
