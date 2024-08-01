#ifndef COLOR_H
# define COLOR_H

#include <stdbool.h>

// Define function pointer types
typedef struct s_color (*create_color_func)(float red, float green, float blue);
typedef bool (*equal_color_func)(struct s_color c1, struct s_color c2);
typedef struct s_color (*add_color_func)(struct s_color c1, struct s_color c2);
typedef struct s_color (*subtract_color_func)(struct s_color c1, struct s_color c2);
typedef struct s_color (*multiply_color_by_scalar_func)(struct s_color c, float scalar);
typedef struct s_color (*multiply_colors_func)(struct s_color c1, struct s_color c2);

typedef struct s_color
{
    float red;
    float green;
    float blue;
    create_color_func create;
    equal_color_func equal;
    add_color_func add;
    subtract_color_func subtract;
    multiply_color_by_scalar_func multiply;
    multiply_colors_func multiply_colors;
}               t_color;

typedef struct s_canvas
{
    int width;
    int height;
    t_color **pixels;
}               t_canvas;

t_color create_color(float red, float green, float blue);
bool equal_color(t_color c1, t_color c2);
t_color add_color(t_color c1, t_color c2);
t_color subtract_color(t_color c1, t_color c2);
t_color multiply_color_by_scalar(t_color c, float scalar);
t_color multiply_colors(t_color c1, t_color c2);

#endif