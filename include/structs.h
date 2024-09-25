/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:28:21 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/25 18:58:51 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "MLX42/MLX42.h"
# include <libft.h>

# include "tuple.h"
# include "matrix.h"
# include "window.h"
# include "error.h"
# include "parser.h"
# include <math.h>
# include <fcntl.h>  // open
# include <unistd.h> // close, read, write
# include <stdio.h>  // printf, perror
# include <stdlib.h> // malloc, free, exit
# include <string.h> // strerror

# define WIDTH 800 // Canvas pixels
# define HEIGHT 600
# define WALL_SIZE 7.0
# define WALL_Z 10.0
# define RAY_ORIGIN_X 0.0
# define RAY_ORIGIN_Y 0.0
# define RAY_ORIGIN_Z -5.0

#define BLACK 0x000000FF
//#define RED 0xFF0000FF

// ANSI escape codes for colors and effects
# define RESET "\033[0m"
# define BOLD "\033[1m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

# define BPP sizeof(int32_t) /* Only support RGBA */

typedef struct s_shape t_shape;

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}				t_ray;

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}				t_color;

typedef struct s_light
{
	t_tuple	position;
	t_color	intensity; // Intensity, color of the light source, va
	float	brightness;	// Brightness, value between 0 and 1
	bool	flag;
}				t_light;


typedef struct s_material
{
	t_color		color; // Color of the object
	float		ambient; // Ambient light, value between 0 and 1
	float		diffuse; // Diffuse light, value between 0 and 1
	float		specular; // Specular light, value between 0 and 1
	float		shininess; // Shininess, value between 10 (very large highlight) and 200 (small highlight)
	bool		flag;
}				t_material;


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

typedef struct s_intersection
{
	float	t;
	t_shape	*object; // Use void* to allow for different types of objects
}			t_intersection;

typedef struct s_intersections
{
	int				count; // Number of intersections
	t_intersection	*array; // Array of intersections

}				t_intersections;


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


typedef struct s_world
{
    t_light		light;
    t_shape		*object;
    int			count;
    t_window	window;
	t_camera	camera;
}				t_world;

/* RAY.C */
t_ray			ray(t_tuple origin, t_tuple direction);
t_tuple			position(t_ray r, float t);
t_ray			transform(t_ray r, t_matrix *m);

/* ROTATION.C*/
t_matrix		*rotation_x(float radians);
t_matrix		*rotation_y(float radians);
t_matrix		*rotation_z(float radians);

/* LIGHT.C */
t_light			point_light(t_tuple position, t_color intensity);
t_color			lighting_shadow(t_material *material, t_light *light, 
							t_tuple over_point, t_tuple eyev, 
							t_tuple normalv, bool in_shadow);

/* MATERIALS.C */
t_color			color(float r, float g, float b);
t_material		material();
bool			color_equal(t_color a, t_color b, float epsilon);
void			print_color(t_color c);

/* INTERSECTIONS.C */
t_intersection	intersection(float t, t_shape *shape);
t_intersections	intersections_array(int count, t_intersection *array);
t_computations	prepare_computations(t_intersection i, t_ray r);

/* CAMERA.C */
t_camera		camera(double hsize, double vsize, double field_of_view);
void			setup_camera(t_camera camera);
t_ray			ray_for_pixel(t_camera camera, int px, int py);
uint32_t		color_to_pixel(t_color color);
t_color			color_from_pixel(uint32_t pixel);
void			render(mlx_image_t *img, t_camera camera, t_world *world);

/* WORLD.C */
t_intersections	intersect_world(t_world *w, t_ray r);
t_intersections	add_intersections(t_intersections xs, t_intersections temp);
t_world			*default_world();
void			sort_intersections(t_intersections *xs);
t_color			shade_hit_shadow(t_world *world, t_computations comps);
t_color			color_at(t_world *world, t_ray r);
t_world			*create_scene(char *filename);
bool			is_shadowed(t_world *world, t_tuple over_point);
void			destroy_world(t_world *w);

/* COLOR_MATH.C */
t_color			multiply_color(t_color c1, t_color c2);
t_color			multiply_color_by_scalar(t_color c, float scalar);
t_color			add_color(t_color c1, t_color c2);



/* PRINT.C */
void print_lighting_shadow(t_material *material, t_light *light, t_tuple point, t_tuple eyev, t_tuple normalv, bool in_shadow);
void print_world(t_world *w);
void print_hit_info(t_world *world, t_computations *comps, t_color *result, int x, int y, t_camera *camera, t_intersection *hit_p);
void print_material(t_material *material);
void print_sp(t_shape *shape);


#endif
