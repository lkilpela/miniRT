/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:28:21 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/25 15:42:58 by lkilpela         ###   ########.fr       */
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
# include "shapes.h"
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

/**
 * @brief Represents a ray in 3D space.
 *
 * @param origin The starting point of the ray, represented as a t_tuple.
 * @param direction The direction vector of the ray, represented as a t_tuple.
 */
typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}				t_ray;

/**
 * @brief Represents a color in RGB format.
 *
 * @param r The red component of the color.
 * @param g The green component of the color.
 * @param b The blue component of the color.
 */
typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}				t_color;

/**
 * @brief Represents a light source in 3D space.
 * 
 * @param position The position of the light source, represented as a t_tuple.
 * @param intensity The intensity of the light source, represented as a t_color.
 */
typedef struct s_light
{
	t_tuple	position;
	t_color	intensity; // Intensity, color of the light source, va
	float	brightness;	// Brightness, value between 0 and 1
	bool	flag;
}				t_light;

typedef struct s_ambient
{
	t_color	color;
	float	ratio;
	bool	flag;
}				t_ambient;

/**
 * @brief Represents a material with properties for lighting calculations.
 * 
 * @param color The color of the object.
 * @param ambient The ambient light of the object.
 * @param diffuse The diffuse light of the object.
 * @param specular The specular light of the object.
 * @param shininess The shininess of the object.
 */
typedef struct s_material
{
	t_color		color; // Color of the object
	t_ambient	ambient; // Ambient light, value between 0 and 1
	float		diffuse; // Diffuse light, value between 0 and 1
	float		specular; // Specular light, value between 0 and 1
	float		shininess; // Shininess, value between 10 (very large highlight) and 200 (small highlight)
}				t_material;

/**
 * @brief Represents the computations for a ray-object intersection.
 * 
 * @param t The time of the intersection.
 * @param shape The shape that was intersected.
 * @param point The point of intersection.
 * @param eyev The eye vector.
 * @param normalv The normal vector.
 * @param over_point The point slightly above the surface.
 * @param inside Whether the intersection is inside the object. 
 */
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

/**
 * @brief Represents an intersection between a ray and an object.
 * 
 * @param t The time of the intersection.
 * @param object The object that was intersected.
 */
typedef struct s_intersection
{
	float	t;
	t_shape	*object; // Use void* to allow for different types of objects
}			t_intersection;

/**
 * @brief Represents an array of intersections.
 * 
 * @param count The number of intersections.
 * @param array The array of intersections. 
 */
typedef struct s_intersections
{
	int				count; // Number of intersections
	t_intersection	*array; // Array of intersections

}				t_intersections;

/**
 * @brief Represents a camera in 3D space.
 * 
 * @param hsize The horizontal size of the camera.
 * @param vsize The vertical size of the camera.
 * @param field_of_view The field of view of the camera.
 * @param half_width The half width of the camera.
 * @param half_height The half height of the camera.
 * @param pixel_size The size of a pixel.
 * @param transform The transformation matrix of the camera.
 */
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

/**
 * @brief Represents a world with objects and light sources.
 * 
 * @param light The light source in the world.
 * @param spheres The array of spheres in the world.
 * @param count The number of spheres in the world. 
 */
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
t_color			lighting_shadow(t_material *m, t_light *light, 
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
void			setup_camera(t_camera *camera);
t_ray			ray_for_pixel(t_camera *camera, int px, int py);
uint32_t		color_to_pixel(t_color color);
t_color			color_from_pixel(uint32_t pixel);
void			render(mlx_image_t *img, t_camera *camera, t_world *world);

/* WORLD.C */
t_intersections	intersect_world(t_world *w, t_ray r);
t_intersections	add_intersections(t_intersections xs, t_intersections temp);
t_world			*default_world();
void			sort_intersections(t_intersections *xs);
t_color			shade_hit(t_world *world, t_computations comps);
t_color			shade_hit_shadow(t_world *world, t_computations comps);
t_color			color_at(t_world *world, t_ray r);
//t_color		color_at(t_world *world, t_ray r, int x, int y, t_camera *camera);
t_world			*create_scene();
bool			is_shadowed(t_world *world, t_tuple over_point);

/* COLOR_MATH.C */
t_color			multiply_color(t_color c1, t_color c2);
t_color			multiply_color_by_scalar(t_color c, float scalar);
t_color			add_color(t_color c1, t_color c2);

/* PRINT.C */
void print_lighting_shadow(t_material *m, t_light *light, t_tuple point, t_tuple eyev, t_tuple normalv, bool in_shadow);
void print_world(t_world *w);
void print_hit_info(t_world *world, t_computations *comps, t_color *result, int x, int y, t_camera *camera, t_intersection *hit_p);
void print_material(t_material *m);
void print_sp(t_shape *shape);


#endif
