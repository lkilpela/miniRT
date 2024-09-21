#ifndef TUPLE_H
# define TUPLE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h> // For fabs function

#define EPSILON 0.00001

typedef struct s_tuple //point
{
    float x;
    float y;
    float z;
    float w;
}              t_tuple;

t_tuple create_tuple(float x, float y, float z, float w);
bool equal(float a, float b);
bool equal_tuple(t_tuple a, t_tuple b);
float magnitude(t_tuple v);

t_tuple point(float x, float y, float z);
t_tuple vector(float x, float y, float z);


t_tuple add(t_tuple a1, t_tuple a2);
t_tuple normalize(t_tuple v);
t_tuple multiply_by_scalar(t_tuple t, float scalar);
t_tuple subtract(t_tuple p1, t_tuple p2);
float dot(t_tuple a, t_tuple b);
t_tuple reflect(t_tuple in, t_tuple normal);
t_tuple negate(t_tuple t);

bool equal_tuples(t_tuple a, t_tuple b, float epsilon);
void print_tuple(t_tuple t);
//void test_dot_product();
//void test_cross_product();
//void test_color();
//void test_canvas();
//void test_write_pixel();
//void test_canvas_to_ppm();

#endif