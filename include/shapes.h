/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:54:27 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/26 08:46:43 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

/* Project-Specific Includes */
# include "structs.h"

/* Macros for Shapes
# define SHAPE_AS_PLANE(shape) ((t_plane *)(shape)->object)
# define SHAPE_AS_SPHERE(shape) ((t_sphere *)(shape)->object)
# define SHAPE_AS_CYLINDER(shape) ((t_cylinder *)(shape)->object) */

/* Function Pointers */
typedef struct s_intersections	(*t_local_intersect_func)(struct s_shape *shape,
							struct s_ray ray);
typedef struct s_tuple			(*t_local_normal_func)(struct s_shape *shape,
							struct s_tuple point);

/* SHAPES STRUCT */
typedef struct s_sphere
{
	t_tuple	center;
	float	radius;
}				t_sphere;

typedef struct s_plane
{
	t_tuple	point;
	t_tuple	normal;
}				t_plane;

typedef struct s_cylinder
{
	float	minimum;
	float	maximum;
	bool	closed;
}				t_cylinder;

typedef struct s_shape
{
	int						id;
	void					*object;
	t_matrix				*transform;
	t_material				material;
	t_local_intersect_func	local_intersect;
	t_local_normal_func		local_normal_at;
}				t_shape;

/* SHAPES.C */
t_shape			*shape(void);
void			set_transform_shape(t_shape *shape, t_matrix *m);
t_intersections	intersect_shape(t_shape *shape, t_ray ray);
t_tuple			normal_at_shape(t_shape *shape, t_tuple world_point);

/* SPHERE.C */
t_shape			*sphere(void);
//t_shape			*sphere_2(t_sphere* sp);
t_intersections	local_intersect_sphere(t_shape *shape, t_ray r);
//t_intersections	intersect_transformation(t_shape *s, t_ray r);
t_intersection	*hit(t_intersections *intersections);
t_tuple			local_normal_at_sphere(t_shape *shape, t_tuple point);
void			set_sphere_params(t_shape *shape, t_tuple center, float radius);

/* PLANE.C */
t_shape			*plane(void);
t_intersections	local_intersect_plane(t_shape *shape, t_ray r);
t_tuple			local_normal_at_plane(t_shape *shape, t_tuple point);
void			set_transform_shape(t_shape *shape, t_matrix *m);

/* CYLINDER.C */
t_shape			*cylinder(void);
t_intersections	local_intersect_cylinder(t_shape *shape, t_ray r);
void			intersect_caps(t_shape *shape, t_ray r, t_intersections result);
bool			check_cap(t_ray r, float t);
t_tuple			local_normal_at_cylinder(t_shape *shape, t_tuple point);

#endif
