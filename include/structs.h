/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:28:21 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/23 22:30:43 by lkilpela         ###   ########.fr       */
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
#define HEIGHT 50
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

typedef struct s_color
{
    float r;
    float g;
    float b;
}               t_color;

typedef struct s_light
{
    t_tuple position;
    t_color intensity;
}               t_light;


typedef struct s_material
{
    t_color color; // Color of the object
    float ambient; // Ambient light, value between 0 and 1
    float diffuse; // Diffuse light, value between 0 and 1
    float specular; // Specular light, value between 0 and 1
    float shininess; // Shininess, value between 10 (very large highlight) and 200 (small highlight)
}               t_material;

typedef struct s_shape
{
    int id;
    //t_matrix *transform;
    //t_material material;
    void* object;
}               t_shape;


typedef struct s_sphere
{
    t_tuple center;
    float radius;
    t_matrix *transform;
    struct s_material material;
}               t_sphere;

typedef struct s_computations
{
    double t;
    t_sphere *shape;
    t_tuple point;
    t_tuple eyev;
    t_tuple normalv;
    bool inside;
} t_computations;

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

typedef struct s_camera {
    double hsize;
    double vsize;
    double field_of_view;
    double half_width;
    double half_height;
    double pixel_size;
    t_matrix *transform;
} t_camera;

typedef struct s_world
{
    t_light light;
    t_sphere *spheres;
    int count;
}           t_world;


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
t_tuple         normal_at(t_sphere *s, t_tuple p);

/* ROTATION.C*/
t_matrix        *rotation_x(float radians);
t_matrix        *rotation_y(float radians);
t_matrix        *rotation_z(float radians);

/*CANVAS.C*/
t_canvas        canvas(int width, int height);
void            write_pixel(t_canvas *c, int x, int y, uint32_t color);
void            draw_scene(t_canvas *c, t_sphere *s, t_light *light);

/* LIGHT.C */
t_light         point_light(t_tuple position, t_color intensity);
t_color         lighting(t_material *m, t_light *light, t_tuple point, t_tuple eyev, t_tuple normalv);

/* MATERIALS.C */
t_color         color(float r, float g, float b);
t_material      material();
bool            color_equal(t_color a, t_color b, float epsilon);
void            print_color(t_color c);

/* INTERSECTIONS.C */
t_computations  prepare_computations(t_intersection i, t_ray r);

/* CAMERA.C */
t_camera        camera(double hsize, double vsize, double field_of_view);
void            setup_camera(t_camera *camera);
t_ray           ray_for_pixel(t_camera *camera, int px, int py);
uint32_t        color_to_pixel(t_color color);
t_color         color_from_pixel(uint32_t pixel);
void            render(mlx_image_t *img, t_camera *camera, t_world *world);

/* WORLD.C */
t_intersections intersect_world(t_world *w, t_ray r);
t_intersections add_intersections(t_intersections xs, t_intersections temp);
t_world         *default_world();
void            sort_intersections(t_intersections *xs);
t_color         shade_hit(t_world *world, t_computations comps);
//t_color         color_at(t_world *world, t_ray r);
t_color         color_at(t_world *world, t_ray r, int x, int y, t_camera *camera);
t_world         *create_scene();

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
void test_normal_at();
void    test_material();
void test_lighting();
void test_world();
void test_precomputations();
void test_shading();
void test_view_transformation();
void test_setup_camera();
void test_render();
#endif
