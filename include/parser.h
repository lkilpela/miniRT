/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:39:49 by jlu               #+#    #+#             */
/*   Updated: 2024/09/25 15:52:03 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

typedef enum e_id
{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	UNKNOWN
}			t_id;

/* SCENE */
t_id	get_identifier(char *str);
void	parse_scene(char *filename, t_world *w);

/* OBJECTS */
void	parse_plane(char **info, t_world *w);
void	parse_sphere(char **info, t_world *w);
void	parse_cylinder(char **info, t_world *w);

/* UTILS */
void	parse_color(char *str, t_color color);
void	parse_vector(char *str, t_tuple vector);
void	space_replace(char *str);
int		is_valid_identifier(t_id id);

#endif