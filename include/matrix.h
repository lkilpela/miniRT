#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "tuple.h"

typedef struct s_matrix
{
    float **data;
    int x; // cols
    int y; // rows
}               t_matrix;


t_matrix    *allocate_matrix(int y, int x);
t_matrix    *create_matrix(int x, int y, float values[y][x]);
void        destroy_matrix(t_matrix *m);
void        print_matrix(t_matrix *m);
bool        matrices_are_equal(t_matrix *a, t_matrix *b);
float       get_matrix_element(t_matrix *matrix, int row, int col);

t_matrix    *multiply_matrices(t_matrix *a, t_matrix *b);
t_tuple     matrix_multiply_tuple(t_matrix *m, t_tuple t);


t_matrix    *identity_matrix(int size);
t_matrix    *transpose_matrix(t_matrix *a);
float       determinant_2x2(t_matrix *a);
float       determinant(t_matrix *m);
t_matrix    *submatrix(t_matrix *a, int row, int col);
float       minor(t_matrix *a, int row, int col);
float       cofactor(t_matrix *a, int row, int col);
t_matrix    *inverse(t_matrix *m);
bool        float_equals(float a, float b, float epsilon);

t_matrix    *rotation_x(float radians);

#endif