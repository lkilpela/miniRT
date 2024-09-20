typedef struct s_matrix
{
    float **data;
    int x; // cols
    int y; // rows
}               t_matrix;

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

float determinant(t_matrix *m);
bool float_equals(float a, float b, float epsilon);

// Function to allocate memory for the matrix
t_matrix* allocate_matrix(int y, int x)
{
    t_matrix *m = calloc(1, sizeof(t_matrix));
    if (!m)
        return NULL;
    m->x = x;
    m->y = y;
    m->data = calloc(y, sizeof(float *));
    if (!m->data)
    {
        free(m);
        return NULL;
    }
    int i = 0;
    while (i < y)
    {
        m->data[i] = calloc(x, sizeof(float));
        if (!m->data[i]) {
            for (int j = 0; j < i; j++) {
                free(m->data[j]);
            }
            free(m->data);
            free(m);
            return NULL;
        }
        i++;
    }
    return m;
}

t_matrix *create_matrix(int x, int y, float values[y][x])
{
    t_matrix *m = allocate_matrix(y, x);
    if (!m)
        return NULL;
    int i = 0;
    while (i < y)
    {
        int j = 0;
        while (j < x)
        {
            m->data[i][j] = values[i][j];
            j++;
        }
        i++;
    }
    return m;
}

void destroy_matrix(t_matrix *m)
{
    if (m)
    {
        for (int i = 0; i < m->y; i++)
        {
            free(m->data[i]);
        }
        free(m->data);
        free(m);
    }
}

float get_matrix_element(t_matrix *matrix, int row, int col)
{
    return matrix->data[row][col];
}

t_matrix *multiply_matrices(t_matrix *a, t_matrix *b)
{
    t_matrix *m;

    if (a->x != b->y)
    {
        fprintf(stderr, "Matrix dimensions are not compatible for multiplication\n");
        return NULL; // Matrices can not be multiplied
    }
    m = allocate_matrix(a->y, b->x);
    if (!m)
        return NULL;
    int i = 0;
    while (i < a->y)
    {
        int j = 0;
        while (j < b->x)
        {
            int k = 0;
            while (k < a->x)
            {
                m->data[i][j] += a->data[i][k] * b->data[k][j];
                k++;
            }
            j++;
        }
        i++;
    }
    return m;

}

t_tuple matrix_multiply_tuple(t_matrix *m, t_tuple t)
{
    t_tuple result;
    result.x = get_matrix_element(m, 0, 0) * t.x + get_matrix_element(m, 0, 1) * t.y + get_matrix_element(m, 0, 2) * t.z + get_matrix_element(m, 0, 3) * t.w;
    result.y = get_matrix_element(m, 1, 0) * t.x + get_matrix_element(m, 1, 1) * t.y + get_matrix_element(m, 1, 2) * t.z + get_matrix_element(m, 1, 3) * t.w;
    result.z = get_matrix_element(m, 2, 0) * t.x + get_matrix_element(m, 2, 1) * t.y + get_matrix_element(m, 2, 2) * t.z + get_matrix_element(m, 2, 3) * t.w;
    result.w = get_matrix_element(m, 3, 0) * t.x + get_matrix_element(m, 3, 1) * t.y + get_matrix_element(m, 3, 2) * t.z + get_matrix_element(m, 3, 3) * t.w;
    return result;
}

// Function to print a matrix
void print_matrix(t_matrix *m) {
    for (int i = 0; i < m->y; i++) {
        for (int j = 0; j < m->x; j++) {
            printf("%f ", m->data[i][j]);
        }
        printf("\n");
    }
}

/*
identity =
1 0 0 0
0 1 0 0
0 0 1 0
0 0 0 1
*/
t_matrix* identity_matrix(int size)
{
    t_matrix *m = allocate_matrix(size, size);
    if (!m)
        return NULL;
    for (int i = 0; i < size; i++) {
        m->data[i][i] = 1.0;
    }
    return m;
}

// Function to check if two matrices are equal
bool matrices_are_equal(t_matrix *a, t_matrix *b) {
    if (a->x != b->x || a->y != b->y) {
        return false;
    }
    for (int i = 0; i < a->y; i++) {
        for (int j = 0; j < a->x; j++) {
            if (!float_equals(a->data[i][j], b->data[i][j], 0.001)){
                return false;
            }
        }
    }
    return true;
}

/* TRANSPOSING MATRICES
** Transposing a matrix means to switch its rows and columns.
** For example, the transpose of the following matrix:
** 1 2 3
** 4 5 6
** is:
** 1 4
** 2 5
** 3 6
*/
t_matrix* transpose_matrix(t_matrix *a) 
{
    t_matrix *t = allocate_matrix(a->x, a->y); // Note the swapped dimensions
    if (!t)
        return NULL;
    for (int i = 0; i < a->y; i++) {
        for (int j = 0; j < a->x; j++) {
            t->data[j][i] = a->data[i][j];
        }
    }
    return t;
}


/* INVERTING 2x2 MATRICES
** determinant = ad - bc 
** If determinant is 0, the matrix is not invertible (no solution)
*/
float determinant_2x2(t_matrix *a) 
{
    if (a->x != 2 || a->y != 2) {
        fprintf(stderr, "Matrix is not 2x2\n");
        return 0; // or handle error appropriately
    }
    return a->data[0][0] * a->data[1][1] - a->data[0][1] * a->data[1][0];
}

// Function to compare two floating-point numbers with a tolerance
bool float_equals(float a, float b, float epsilon) {
    return fabs(a - b) < epsilon;
}

/* SUBMATRICES
** A submatrix is a matrix that is derived from another matrix by removing one or more of its rows and/or columns.
** For example, the submatrix of the following matrix, removing the first row and the last column:
** 1 2 3 <- Remove this row
** 4 5 6
** 7 8 9
**     ^ Remove this column
** is:
** 4 5
** 7 8
** To find the submatrix, we remove the row and column specified by the arguments.
*/
t_matrix* submatrix(t_matrix *a, int row, int col) {
    t_matrix *sub = allocate_matrix(a->y - 1, a->x - 1);
    if (!sub)
        return NULL;
    int sub_i = 0, sub_j = 0;
    for (int i = 0; i < a->y; i++) {
        if (i == row) continue;
        sub_j = 0;
        for (int j = 0; j < a->x; j++) {
            if (j == col) continue;
            sub->data[sub_i][sub_j] = a->data[i][j];
            sub_j++;
        }
        sub_i++;
    }
    return sub;
}


/* MANIPULATING MINORS
** A minor is the determinant of the submatrix that results from removing the i-th row and j-th column of a matrix.
** For example, the minor of the following matrix, removing the first row and the last column:
** 1 2 3 <- Remove this row
** 4 5 6
** 7 8 9
**     ^ Remove this column
** is:
** 5 6
** 8 9
** To find the minor, we first find the submatrix, then calculate the determinant of the submatrix.
*/
float minor(t_matrix *a, int row, int col)
{
    t_matrix *sub = submatrix(a, row, col);
    float det = determinant(sub);
    destroy_matrix(sub);
    return det;
}

/* COMPUTING COFACTORS
** Compute the minor at a given row and column.
** if row + col is even, the cofactor is the minor.
** if row + col is odd, the cofactor is the negative of the minor.
*/
float cofactor(t_matrix *a, int row, int col) {
    float minor_value = minor(a, row, col);
    if ((row + col) % 2 != 0) {
        return -minor_value;
    }
    return minor_value;
}

/* COMPUTING DETERMINANTS FOR LARGER MATRICES
** The determinant of a 2x2 matrix is ad - bc.
** Multiplying the element by its cofactor and add the results.
*/
float determinant(t_matrix *m)
{
    if (m->x != m->y) {
        fprintf(stderr, "Matrix is not square\n");
        return 0; // or handle error appropriately
    }

    if (m->x == 2) {
        return determinant_2x2(m);
    }

    float det = 0;
    for (int col = 0; col < m->x; col++) {
        det += m->data[0][col] * cofactor(m, 0, col);
    }

    return det;
}

/* INVERTING MATRICES
** The inverse of a matrix A is denoted A^-1.
** The inverse of a matrix is the matrix that, when multiplied with the original matrix, gives the identity matrix.
** The inverse of a matrix is calculated by:
** 1. Calculating the determinant of the matrix.
** 2. Calculating the matrix of cofactors.
** 3. Transposing the matrix of cofactors.
** 4. Dividing the transposed matrix of cofactors by the determinant.
** 
*/
t_matrix* inverse(t_matrix *m)
{
    float det = determinant(m);
    if (float_equals(det, 0.0, 0.001)) {
        fprintf(stderr, "Matrix is not invertible\n");
        return NULL; // or handle error appropriately
    }

    t_matrix *m2 = allocate_matrix(m->y, m->x);
    if (!m2)
        return NULL;

    for (int row = 0; row < m->y; row++) {
        for (int col = 0; col < m->x; col++) {
            float c = cofactor(m, row, col);
            m2->data[col][row] = c / det; // Note the transpose operation
        }
    }
    return m2;
}

int main() {
    // Test 1: Inverse of a 4x4 matrix
    float valuesA1[4][4] = {
        {8, -5, 9, 2},
        {7, 5, 6, 1},
        {-6, 0, 9, 6},
        {-3, 0, -9, -4}
    };
    t_matrix *A1 = create_matrix(4, 4, valuesA1);

    float valuesA1_inv_expected[4][4] = {
        {-0.15385, -0.15385, -0.28205, -0.53846},
        {-0.07692, 0.12308, 0.02564, 0.03077},
        {0.35897, 0.35897, 0.43590, 0.92308},
        {-0.69231, -0.69231, -0.76923, -1.92308}
    };
    t_matrix *A1_inv_expected = create_matrix(4, 4, valuesA1_inv_expected);

    t_matrix *A1_inv = inverse(A1);

    if (matrices_are_equal(A1_inv, A1_inv_expected)) {
        printf("Test 1 passed: inverse(A1) is correct\n");
    } else {
        printf("Test 1 failed: inverse(A1) is incorrect\n");
    }

    destroy_matrix(A1);
    destroy_matrix(A1_inv);
    destroy_matrix(A1_inv_expected);

    // Test 2: Inverse of another 4x4 matrix
    float valuesA2[4][4] = {
        {9, 3, 0, 9},
        {-5, -2, -6, -3},
        {-4, 9, 6, 4},
        {-7, 6, 6, 2}
    };
    t_matrix *A2 = create_matrix(4, 4, valuesA2);

    float valuesA2_inv_expected[4][4] = {
        {-0.04074, -0.07778, 0.14444, -0.22222},
        {-0.07778, 0.03333, 0.36667, -0.33333},
        {-0.02901, -0.14630, -0.10926, 0.12963},
        {0.17778, 0.06667, -0.26667, 0.33333}
    };
    t_matrix *A2_inv_expected = create_matrix(4, 4, valuesA2_inv_expected);

    t_matrix *A2_inv = inverse(A2);

    if (matrices_are_equal(A2_inv, A2_inv_expected)) {
        printf("Test 2 passed: inverse(A2) is correct\n");
    } else {
        printf("Test 2 failed: inverse(A2) is incorrect\n");
    }

    destroy_matrix(A2);
    destroy_matrix(A2_inv);
    destroy_matrix(A2_inv_expected);

    // Test 3: Multiplying a product by its inverse
    /*“if you multiply some matrix A by another matrix B, producing C,
    you can multiply C by the inverse of B to get A again.”*/
    float valuesA3[4][4] = {
        {3, -9, 7, 3},
        {3, -8, 2, -9},
        {-4, 4, 4, 1},
        {-6, 5, -1, 1}
    };
    t_matrix *A3 = create_matrix(4, 4, valuesA3);

    float valuesB3[4][4] = {
        {8, 2, 2, 2},
        {3, -1, 7, 0},
        {7, 0, 5, 4},
        {6, -2, 0, 5}
    };
    t_matrix *B3 = create_matrix(4, 4, valuesB3);

    t_matrix *C3 = multiply_matrices(A3, B3);
    t_matrix *B3_inv = inverse(B3);
    t_matrix *result = multiply_matrices(C3, B3_inv);

    if (result && matrices_are_equal(result, A3)) {
        printf("Test 3 passed: C3 * inverse(B3) = A3\n");
    } else {
        printf("Test 3 failed: C3 * inverse(B3) != A3\n");
    }

    destroy_matrix(A3);
    destroy_matrix(B3);
    destroy_matrix(C3);
    destroy_matrix(B3_inv);
    destroy_matrix(result);


    /*// Test 1: Submatrix of a 3x3 matrix
    float valuesA[3][3] = {
        {1, 2, 6},
        {-5, 8, -4},
        {2, 6, 4}
    };
    t_matrix *A = create_matrix(3, 3, valuesA);

    float valuesSub[2][2] = {
        {-1, -7},
        {-1, 5}
    };
    t_matrix *Sub_expected = create_matrix(2, 2, valuesSub);

    t_matrix *Sub = submatrix(A, 0, 0);

    if (matrices_are_equal(Sub, Sub_expected)) {
        printf("Test 1 passed: submatrix(A, 0, 0) is correct\n");
    } else {
        printf("Test 1 failed: submatrix(A, 0, 0) is incorrect\n");
    }

    // Compute determinant of Sub
    float det_Sub = determinant_2x2(Sub);

    // Check if determinant of Sub is correct
    if (float_equals(det_Sub, -12.0, 0.0001)) {
        printf("Test passed: determinant(Sub) = -12\n");
    } else {
        printf("Test failed: determinant(Sub) != -12\n");
    }

     // Compute minor of A at (0, 0)
    float minor_A_00 = minor(A, 0, 0);

    // Check if minor of A is correct
    if (float_equals(minor_A_00, -12.0, 0.0001)) {
        printf("Test passed: minor(A, 0, 0) = -12\n");
    } else {
        printf("Test failed: minor(A, 0, 0) != -12\n");
    }

    // Compute cofactor of A at (0, 0)
    float cofactor_A_00 = cofactor(A, 0, 0);

    // Check if cofactor of A at (0, 0) is correct
    if (float_equals(cofactor_A_00, 56.0, 0.0001)) {
        printf("Test passed: cofactor(A, 0, 0) = 56\n");
    } else {
        printf("Test failed: cofactor(A, 0, 0) != 56\n");
    }

    // Compute minor of A at (1, 0)
    float minor_A_10 = minor(A, 0, 1);

    // Check if minor of A at (1, 0) is correct
    if (float_equals(minor_A_10, 25.0, 0.0001)) {
        printf("Test passed: minor(A, 1, 0) = 25\n");
    } else {
        printf("Test failed: minor(A, 1, 0) != 25\n");
    }

    // Compute cofactor of A at (1, 0)
    float cofactor_A_10 = cofactor(A, 1, 0);

    // Check if cofactor of A at (1, 0) is correct
    if (float_equals(cofactor_A_10, -25.0, 0.0001)) {
        printf("Test passed: cofactor(A, 1, 0) = -25\n");
    } else {
        printf("Test failed: cofactor(A, 1, 0) != -25\n");
    }

    // Compute determinant of A
    float det_A = determinant(A);

    // Check if determinant of A is correct
    if (float_equals(det_A, -196.0, 0.0001)) {
        printf("Test passed: determinant(A) = -196\n");
    } else {
        printf("Test failed: determinant(A) != -196\n");
    }


    destroy_matrix(A);
    destroy_matrix(Sub);
    destroy_matrix(Sub_expected);

    // Test 2: Submatrix of a 4x4 matrix
    float valuesA2[4][4] = {
        {-6, 1, 1, 6},
        {-8, 5, 8, 6},
        {-1, 0, 8, 2},
        {-7, 1, -1, 1}
    };
    t_matrix *A2 = create_matrix(4, 4, valuesA2);

    float valuesSub2[3][3] = {
        {-6, 1, 6},
        {-8, 8, 6},
        {-7, -1, 1}
    };
    t_matrix *Sub2_expected = create_matrix(3, 3, valuesSub2);

    t_matrix *Sub2 = submatrix(A2, 2, 1);

    if (matrices_are_equal(Sub2, Sub2_expected)) {
        printf("Test 2 passed: submatrix(A2, 2, 1) is correct\n");
    } else {
        printf("Test 2 failed: submatrix(A2, 2, 1) is incorrect\n");
    }

    destroy_matrix(A2);
    destroy_matrix(Sub2);
    destroy_matrix(Sub2_expected);*/

    return 0;
}

