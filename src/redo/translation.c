#include "/home/lkilpela/miniRT_learning/include/structs.h"

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

float get_matrix_element(t_matrix *matrix, int row, int col)
{
    return matrix->data[row][col];
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
git config --global user.name "Your Name"

// Translating a ray
t_ray transform(t_ray r, t_matrix m)
{
    t_ray transformed_ray;

    transformed_ray.origin = multiply_matrices(m, r.origin);

    t_tuple direction = r.direction;
    direction.w = 0;

    transformed_ray.direction = matrix_multiply_tuple(m, r.direction);
    return transformed_ray;
}

void test_ray_translation()
{
    t_matrix m = translation(5, -3, 2);
}