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

typedef struct s_canvas (*create_canvas_func)(int width, int height);
typedef void (*destroy_canvas_func)(struct s_canvas *canvas);
typedef void (*write_pixel_func)(struct s_canvas *canvas, int x, int y, t_color color);
typedef t_color (*pixel_at_func)(struct s_canvas *canvas, int x, int y);

typedef struct s_canvas
{
    int width;
    int height;
    t_color *pixels;
    create_canvas_func create;
    destroy_canvas_func destroy;
    write_pixel_func write_pixel;
    pixel_at_func pixel_at;
}               t_canvas;

// Color
t_color create_color(float red, float green, float blue);
bool equal_color(t_color c1, t_color c2);
t_color add_color(t_color c1, t_color c2);
t_color subtract_color(t_color c1, t_color c2);
t_color multiply_color_by_scalar(t_color c, float scalar);
t_color multiply_colors(t_color c1, t_color c2);


// Canvas
t_canvas *create_canvas(int width, int height);
void write_pixel(t_canvas *canvas, int x, int y, t_color color);
t_color pixel_at(t_canvas *canvas, int x, int y);
void destroy_canvas(t_canvas *canvas);

#endif