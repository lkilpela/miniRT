/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:54:27 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/26 14:39:17 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

/* Forward Declarations */
typedef struct s_intersection	t_intersection;
typedef struct s_intersections	t_intersections;
typedef struct s_ray			t_ray;
typedef struct s_tuple			t_tuple;
typedef struct s_material		t_material;
typedef struct s_matrix			t_matrix;

/* Function Pointers */
typedef t_intersections	(*t_local_intersect_func)(t_shape *shape, t_ray ray);
typedef t_tuple			(*t_local_normal_func)(t_shape *shape, t_tuple point);

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
	t_tuple	center;
	t_tuple	axis;
	double	radius;
	double	height;
}				t_cylinder;

typedef struct s_shape
{
	int						id;
	void					*object;
	t_matrix				*transform;
	t_material				*material;
	t_local_intersect_func	local_intersect;
	t_local_normal_func		local_normal_at;
}				t_shape;

/* SHAPES.C */
t_shape			*shape(void);
void			set_transform_shape(t_shape *shape, t_matrix *m);
t_intersections	intersect_shape(t_shape *shape, t_ray ray);
t_tuple			normal_at_shape(t_shape *shape, t_tuple world_point);

/* SPHERE.C */
t_shape			*sphere(t_tuple center, float radius);
t_intersections	local_intersect_sphere(t_shape *shape, t_ray r);
t_intersection	*hit(t_intersections *intersections);
t_tuple			local_normal_at_sphere(t_shape *shape, t_tuple point);

/* PLANE.C */
t_shape			*plane(t_tuple point, t_tuple normal);
t_intersections	local_intersect_plane(t_shape *shape, t_ray r);
t_tuple			local_normal_at_plane(t_shape *shape, t_tuple point);


/* CYLINDER.C */
t_shape			*cylinder(t_tuple center, t_tuple axis,
						double radius, double height);
t_intersections	local_intersect_cylinder(t_shape *shape, t_ray r);
void			intersect_caps(t_shape *shape, t_ray r, t_intersections result);
bool			check_cap(t_ray r, float t);
t_tuple			local_normal_at_cylinder(t_shape *shape, t_tuple point);

#endif
