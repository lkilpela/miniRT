/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:28:21 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/21 11:18:35 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <MLX42/MLX42.h>
# include <libft.h>
# include <tuple.h>
# include "matrix.h"
# include <math.h>
# include <fcntl.h>  // open
# include <unistd.h> // close, read, write
# include <stdio.h>  // printf, perror
# include <stdlib.h> // malloc, free, exit
# include <string.h> // strerror

# define WINDOW_WIDTH 1366
# define WINDOW_HEIGHT 768

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
    t_ray transform;
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

//void test_ray();
t_ray ray(t_tuple origin, t_tuple direction);
t_tuple position(t_ray r, float t);
t_intersections intersections_array(int count, t_intersection *array);
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
void test_myltiply_by_inverse_translation();
void test_translation_doesnot_affect_vector();
void test_scaling_applied_to_vector();
void test_multiplying_by_inverse_scaling();
void test_reflection_is_scaling_by_negative_value();
void test_rotate_x_point();
void test_rotate_y_point();
void test_rotate_z_point();
void test_shearing();
void test_chaining_transformations();
void test_ray();
void test_sphere();
#endif
