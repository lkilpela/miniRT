#include "structs.h"
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

t_matrix *matrix_multiply_matrix(t_matrix *a, t_matrix *b)
{
    t_matrix *m;

    if (a->x != b->y)
        return NULL; // Matrices can not be multiplied
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
t_tuple matrix_multiply_tuple(t_matrix m, t_tuple t)
{
    t_tuple result;
    result.x = get_matrix_element(&m, 0, 0) * t.x + get_matrix_element(&m, 0, 1) * t.y + get_matrix_element(&m, 0, 2) * t.z + get_matrix_element(&m, 0, 3) * t.w;
    result.y = get_matrix_element(&m, 1, 0) * t.x + get_matrix_element(&m, 1, 1) * t.y + get_matrix_element(&m, 1, 2) * t.z + get_matrix_element(&m, 1, 3) * t.w;
    result.z = get_matrix_element(&m, 2, 0) * t.x + get_matrix_element(&m, 2, 1) * t.y + get_matrix_element(&m, 2, 2) * t.z + get_matrix_element(&m, 2, 3) * t.w;
    result.w = get_matrix_element(&m, 3, 0) * t.x + get_matrix_element(&m, 3, 1) * t.y + get_matrix_element(&m, 3, 2) * t.z + get_matrix_element(&m, 3, 3) * t.w;
    return result;
}

// Translating a ray
t_ray transform(t_ray r, t_matrix m)
{
    t_ray transformed_ray;

    transformed_ray.origin = matrix_multiply_tuple(m, r.origin);

    t_tuple direction = r.direction;
    direction.w = 0;

    transformed_ray.direction = matrix_multiply_tuple(m, r.direction);
    return transformed_ray;
}

void test_ray_translation()
{
    //t_ray r = ray(point(1, 2, 3), vector(0, 1, 0));
    //t_matrix m = translation(3, 4, 5);
}