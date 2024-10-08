/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:39:49 by jlu               #+#    #+#             */
/*   Updated: 2024/10/09 00:32:41 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* Forward Declarations */
typedef struct s_world	t_world;
typedef struct s_shape	t_shape;
typedef struct s_color	t_color;
typedef struct s_tuple	t_tuple;

/* Identifier */
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

/* PARSER_SCENE.C */
void	parse_scene(char *filename, t_world *w);

/* OBJECTS */
void	parse_plane(char **info, t_world *w);
void	parse_sphere(char **info, t_world *w);
void	parse_cylinder(char **info, t_world *w);
void	add_object(t_world *w, t_shape *object);

/* UTILS */
t_id	get_identifier(char *str);
void	parse_color(char *str, t_color *color);
void	parse_point(char *str, t_tuple *p);
void	parse_vector(char *str, t_tuple *v);
int		is_valid_identifier(t_id id);

#endif
