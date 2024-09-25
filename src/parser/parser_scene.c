/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:46:52 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/17 09:25:12 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "world.h"
#include "error.h"


 // Debug print for parsed info
void	print_parsed_info(char **info)
{
	printf("Parsed info:\n");
	for (int i = 0; info[i] != NULL; i++)
	{
		for (int j = 0; info[i][j] != '\0'; j++)
			printf("info[%d][%d]: %d\n", i, j, info[i][j]);
	}

}

void print_count_elements(char **array)
{
	printf("Number of elements: %d\n", count_elements(array));
}

void	parse_ambient(char **info, t_world *w)
{
	if (w->ambient.flag == false)
	{
		if (count_elements(info) != 3)
			fatal_error("Invalid format: Ambient should have 3 elements\n");
		w->ambient.ratio = ft_atof(info[1]);
		if (w->ambient.ratio < 0 || w->ambient.ratio > 1)
			fatal_error("Ambient light ratio out of range (0-1)\n");
		parse_color(info[2], &w->ambient.color);
		w->ambient.flag = true;
	}
	else
		fatal_error("Ambient light already defined\n");
}

void	parse_camera(char **info, t_world *w)
{
	if (w->camera.flag == false)
	{
		if (count_elements(info) != 4)
			fatal_error("Invalid format: Camera should have 4 elements\n");
		parse_vector(info[1], &w->camera.position);
		parse_vector(info[2], &w->camera.orientation);
		w->camera.orientation = vec3_normalize(w->camera.orientation);
		w->camera.fov = (double)ft_atof(info[3]);
		if (w->camera.fov < 0 || w->camera.fov > 180)
			fatal_error("Camera field of view out of range (0-180)\n");
		w->camera.flag = true;
	}
	else
		fatal_error("Camera already defined\n");
}

void	parse_light(char **info, t_world *w)
{
	if (w->light.flag == false)
	{
		if (count_elements(info) != 3)
			fatal_error("Invalid format: Light should have 3 elements\n");
		parse_vector(info[1], &w->light.position);
		w->light.brightness = (double)ft_atof(info[2]);
		if (w->light.brightness < 0 || w->light.brightness > 1)
			fatal_error("Light brightness out of range (0-1)\n");
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