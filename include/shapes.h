/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:54:27 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/25 14:01:02 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "structs.h"

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

typedef t_intersections (*t_local_intersect_func)(struct s_shape *shape,
												t_ray ray);
typedef t_tuple (*t_local_normal_func)(struct s_shape *shape, t_tuple point);

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
t_shape			*shape();
t_ray			transform_ray_to_object_space(t_shape shape, t_ray ray);
t_tuple			transform_point_to_object_space(t_shape shape, t_tuple point);
t_tuple			transform_normal_to_world_space(t_shape shape, t_tuple normal);
void			set_transform_shape(t_shape *shape, t_matrix *m);
t_intersections	intersect_shape(t_shape *shape, t_ray ray);
t_tuple			normal_at_shape(t_shape *shape, t_tuple world_point);

/* SPHERE.C */
t_shape			*sphere();
t_shape			*sphere_2(t_sphere* sp);
t_intersections	local_intersect_sphere(t_shape *shape, t_ray r);
//t_intersections	intersect_transformation(t_shape *s, t_ray r);
t_intersection	*hit(t_intersections *intersections);
t_tuple			local_normal_at_sphere(t_shape *shape, t_tuple point);

/* PLANE.C */
t_shape			*plane();
t_intersections	local_intersect_plane(t_shape *shape, t_ray r);
t_tuple			local_normal_at_plane(t_shape *shape, t_tuple point);
void			set_transform_shape(t_shape *shape, t_matrix *m);

/* CYLINDER.C */
t_shape			*cylinder();


#endif