/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:28:21 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/21 22:10:39 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "MLX42/MLX42.h"
# include <libft.h>
# include "tuple.h"
# include "matrix.h"
# include <math.h>
# include <fcntl.h>  // open
# include <unistd.h> // close, read, write
# include <stdio.h>  // printf, perror
# include <stdlib.h> // malloc, free, exit
# include <string.h> // strerror

#define WIDTH 100 // Canvas pixels
#define HEIGHT 100
#define WALL_SIZE 7.0
#define WALL_Z 10.0
#define RAY_ORIGIN_X 0.0
#define RAY_ORIGIN_Y 0.0
#define RAY_ORIGIN_Z -5.0

#define BLACK 0x000000FF
#define RED 0xFF0000FF


typedef struct s_ray
{
    t_tuple origin;
    t_tuple direction;
}               t_ray;

typedef struct s_sphere
{
    t_tuple center;
    float radius;
    int id;
    t_matrix *transform;
}               t_sphere;

typedef struct s_intersection
{
    float t;
    void *object; // Use void* to allow for different types of objects
}               t_intersection;

typedef struct s_intersections
{
    int count; // Number of intersections
    t_intersection *array; // Array of intersections

}               t_intersections;

typedef struct s_canvas
{
    int width;
    int height;
    uint32_t *pixels;
}               t_canvas;


/* RAY.C */
t_ray           ray(t_tuple origin, t_tuple direction);
t_tuple         position(t_ray r, float t);
t_ray           transform(t_ray r, t_matrix *m);

/* SPHERE.C */
t_sphere        sphere();
t_intersection  intersection(float t, void *object);
t_intersections intersections_array(int count, t_intersection *array);
t_intersections intersect(t_sphere *s, t_ray *r);
t_intersections intersect_transformation(t_sphere *s, t_ray *r);
t_intersection  *hit(t_intersections *intersections);

/* ROTATION.C*/
t_matrix        *rotation_x(float radians);
t_matrix        *rotation_y(float radians);
t_matrix        *rotation_z(float radians);

/*CANVAS.C*/
t_canvas        canvas(int width, int height);
void            write_pixel(t_canvas *c, int x, int y, uint32_t color);
void            render(t_canvas *c, t_sphere *s);

/* TESTS */
//void test_intersection();
//t_intersections intersect(t_sphere s, t_ray r);
//void test_aggregating_intersections();
//void test_sphere_intersects_2p();
//void test_sphere_intersects_tangent();
//void test_sphere_intersects_raymiss();
//void test_sphere_intersects_rayinside();
//void test_sphere_behind_ray();
//void test_hit_all_positive();
//void test_hit_some_negative();
//void test_hit_all_negative();
//void test_hit_lowest_nonnegative();
//void test_myltiply_by_inverse_translation();
//void test_translation_doesnot_affect_vector();
//void test_scaling_applied_to_vector();
//void test_multiplying_by_inverse_scaling();
//void test_reflection_is_scaling_by_negative_value();
//void test_rotate_x_point();
//void test_rotate_y_point();
//void test_rotate_z_point();
//void test_shearing();
//void test_chaining_transformations();
//void test_ray();
//void test_sphere();
void test_sphere_transformation();
#endif
