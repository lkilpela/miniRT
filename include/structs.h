/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:28:21 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/06 23:20:11 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/* Standard Library Includes */
# include <math.h>	 // sqrt, pow, fabs, INFINITY, M_PI
# include <fcntl.h>  // open
# include <unistd.h> // close, read, write
# include <stdio.h>  // printf, perror
# include <stdlib.h> // malloc, free, exit
# include <string.h> // strerror

/* MLX & Libft Includes */
# include "MLX42/MLX42.h"
# include <libft.h>

/* Project-Specific Includes */
# include "tuple.h"
# include "error.h"
# include "window.h"
# include "matrix.h"
# include "shapes.h"
# include "parser.h"

/* Macros for Visualizing the Scene */
# define WIDTH 500
# define HEIGHT 250
# define WALL_SIZE 7.0
# define WALL_Z 10.0
# define RAY_ORIGIN_X 0.0
# define RAY_ORIGIN_Y 0.0
# define RAY_ORIGIN_Z -5.0

/* Macros for MLX42 Image */
# define BPP sizeof(int32_t) /* Only support RGBA */

/* Macros for Floating Point Comparisons */
# define EPSILON 1e-3

/* ANSI Escape Codes for Colors and Effects */
# define RESET "\033[0m"
# define BOLD "\033[1m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

/* Forward Declarations */
typedef struct s_shape t_shape;
typedef struct s_matrix t_matrix;

/* Struct Definitions */


/* idx */
typedef struct s_idx
{
	int		i;
	int		j;
	int		k;
	int		l;
}				t_idx;

/* RAY */
typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}				t_ray;

/* COLOR */
typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}				t_color;

/* LIGHT */
typedef struct s_light
{
	t_tuple	position;
	t_color	intensity; // Intensity, color of the light source, value between 0 and 1
	float	brightness;	// Brightness, value between 0 and 1
	bool	flag;
}				t_light;

/* MATERIAL */
typedef struct s_material
{
	t_color		color; // Color of the object
	float		diffuse; // Diffuse light, value between 0 and 1
	float		specular; // Specular light, value between 0 and 1
	float		shininess; // Shininess, value between 10 (very large highlight) and 200 (small highlight)
	bool		flag;
}				t_material;

/* Intersections */
typedef struct s_intersection
{
	float	t;
	t_shape	*object;
}			t_intersection;

typedef struct s_intersections
{
	int				count; // Number of intersections
	t_intersection	*array; // Array of intersections

}				t_intersections;

/* COMPUTATIONS */
/* Struct to hold the results of a ray-object intersection */
typedef struct s_computations
{
	double	t;
	t_shape	*shape;
	t_tuple	point;
	t_tuple	eyev;
	t_tuple	normalv;
	t_tuple	over_point;
	bool	inside;
}				t_computations;

/* */
typedef struct s_camera
{
	double		hsize;
	double		vsize;
	double		fov;
	t_tuple		from;
	t_tuple		to;
	t_tuple		up;
	double		half_width;
	double		half_height;
	double		pixel_size;
	t_matrix	*transform;
	bool		flag;
}				t_camera;

typedef struct s_ambient
{
	float	ratio;
	t_color	color;
	bool	flag;
}				t_ambient;

typedef struct s_world
{
	t_light		light;
	t_shape		**objects;
	int			count; // Number of objects in the world
	t_window	window;
	t_camera	camera;
	t_ambient	ambient;
}				t_world;

/* RAY.C */
t_ray			ray(t_tuple origin, t_tuple direction);
t_tuple			position(t_ray r, float t);
t_ray			transform(t_ray r, t_matrix *m);

/* LIGHT.C */
t_light			point_light(t_tuple position, t_color intensity);
t_color			lighting(t_world *w, t_computations comps,
						t_material *material, bool in_shadow);

/* MATERIALS.C */
t_color			color(float r, float g, float b);
t_material		*material();

/* INTERSECTIONS.C */
t_intersection	intersection(float t, t_shape *shape);
t_intersections	intersections_array(int count, t_intersection *array);
t_computations	prepare_computations(t_intersection i, t_ray r);

/* CAMERA.C */
// t_camera		camera(double hsize, double vsize, double field_of_view);
// t_camera		camera(double hsize, double vsize, double field_of_view, t_tuple form, t_tuple to);
t_camera		camera(t_world *w, double field_of_view, t_tuple form, t_tuple to);
void			compute_pixel_size(t_camera *c);
t_ray			ray_for_pixel(t_world *w, int px, int py);
uint32_t		color_to_pixel(t_color color);
t_color			color_from_pixel(uint32_t pixel);
void			render(mlx_image_t *img, t_world *w);

/* WORLD.C */
t_intersections	intersect_world(t_world *w, t_ray r);
t_intersections	add_intersections(t_intersections xs, t_intersections temp);
t_world			*default_world();
void			sort_intersections(t_intersections *xs);
t_color			shade_hit(t_world *world, t_computations comps);
t_color			color_at(t_world *world, t_ray r, int x, int y);
t_world			*create_scene(char *filename);
bool			is_shadowed(t_world *world, t_computations comps);
void			destroy_world(t_world *w);

/* COLOR_MATH.C */
t_color			multiply_color(t_color c1, t_color c2);
t_color			multiply_color_by_scalar(t_color c, float scalar);
t_color			add_color(t_color c1, t_color c2);
void			clamp_color(t_color *c);


/* PRINT.C */
void	print_lighting_shadow(t_material *material, t_light *light, t_tuple point, t_tuple eyev, t_tuple normalv, bool in_shadow);
void	print_hit_info(t_world *world, t_computations *comps, t_color *result, int x, int y, t_camera *camera, t_intersection *hit_p);
void	print_material(t_material *material);
void	print_matrix(t_matrix *m);
void	print_color(t_color c);
void	print_debug_info(t_matrix *inverse_transform, t_tuple local_point, t_tuple local_normal, t_matrix *transpose_inverse_transform, t_tuple world_normal, t_tuple result);
//void	print_shape(t_shape s);
void	print_parsed_info(char **info);
void	print_camera(t_camera camera);
void	print_float(double f);
void	print_ray_for_pixel(double xoffset, double yoffset, double world_x, double world_y, t_matrix *inverse_transform, t_tuple pixel, t_tuple origin, t_tuple direction);
void	print_sp(t_shape *shape);
void	print_plane(t_shape *shape);
void	print_cylinder(t_shape *shape);
void	print_object(t_shape *shape);
void	print_world(t_world *w);
void	print_hit_data(int x, int y, t_computations comps, t_color result, t_ray r, t_intersection *hit_p);
#endif
