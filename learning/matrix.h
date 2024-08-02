#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct s_matrix
{
    float **data;
    int x; // cols
    int y; // rows
}               t_matrix;

t_matrix *create_matrix(int x, int y, float values[y][x]);

#endif