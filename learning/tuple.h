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
