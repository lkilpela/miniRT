#include "matrix.h"

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

void test_2x2() {
    float values[2][2] = {
        {-3, 5},
        {1, -2}
    };

    t_matrix *m = create_matrix(2, 2, values);
    assert(m != NULL);

    assert(get_matrix_element(m, 0, 0) == -3);
    assert(get_matrix_element(m, 0, 1) == 5);
    assert(get_matrix_element(m, 1, 0) == 1);
    assert(get_matrix_element(m, 1, 1) == -2);
    
    destroy_matrix(m);
}

void test_3x3() {
    float values[3][3] = {
        {-3, 5, 0},
        {1, -2, -7},
        {0, 1, 1}
    };

    t_matrix *m = create_matrix(3, 3, values);
    assert(m != NULL);

    assert(get_matrix_element(m, 0, 0) == -3);
    assert(get_matrix_element(m, 1, 1) == -2);
    assert(get_matrix_element(m, 2, 2) == 1);
    
    destroy_matrix(m);
}

void test_4x4() {
    float values[4][4] = {
        {1, 2, 3, 4},
        {5.5, 6.5, 7.5, 8.5},
        {9, 10, 11, 12},
        {13.5, 14.5, 15.5, 16.5}
    };

    t_matrix *m = create_matrix(4, 4, values);
    assert(m != NULL);

    assert(get_matrix_element(m, 0, 0) == 1);
    assert(get_matrix_element(m, 0, 3) == 4);
    assert(get_matrix_element(m, 1, 0) == 5.5);
    assert(get_matrix_element(m, 1, 2) == 7.5);
    assert(get_matrix_element(m, 2, 2) == 11);
    assert(get_matrix_element(m, 3, 0) == 13.5);
    assert(get_matrix_element(m, 3, 2) == 15.5);

    destroy_matrix(m);
}

int main() {
    test_2x2();
    test_3x3();
    test_4x4();
    printf("All tests passed\n");
    return 0;
}