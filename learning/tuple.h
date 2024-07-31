# ifndef STRUCT_H
# define STRUCT_H

typedef struct s_tuple //point
{
    float x;
    float y;
    float z;
    float w;
}              t_tuple;
#endif

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h> // For fabs function

#define EPSILON 0.00001

t_tuple create_tuple(float x, float y, float z, float w);
bool equal(float a, float b);
bool equal_tuple(t_tuple a, t_tuple b);
float magnitude(t_tuple v);

t_tuple point(float x, float y, float z);
t_tuple vector(float x, float y, float z);


t_tuple add(t_tuple a1, t_tuple a2);
t_tuple normalize(t_tuple v);
float magnitude(t_tuple v);


void test_dot_product();
void test_cross_product();