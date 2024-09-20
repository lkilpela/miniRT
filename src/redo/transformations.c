#include "matrix.c"

typedef struct s_tuple //point
{
    float x;
    float y;
    float z;
    float w;
}              t_tuple;


t_tuple create_tuple(float x, float y, float z, float w)
{
    t_tuple t;

    t.x = x;
    t.y = y;
    t.z = z;
    t.w = w;
    return (t);
}

// Factory function to create a point
t_tuple point(float x, float y, float z)
{
    return (create_tuple(x, y, z, 1.0));
}

t_tuple matrix_multiply_tuple(t_matrix *m, t_tuple t);

t_matrix *translation(float x, float y, float z)
{
    t_matrix *m = identity_matrix(4);

    // Set translation values
    m->data[0][3] = x;
    m->data[1][3] = y;
    m->data[2][3] = z;

    return m;
}

void test_translation()
{
    t_matrix *transform = translation(5, -3, 2);
    t_tuple p = point(-3, 4, 5);
    t_tuple expected = point(2, 1, 7);

    t_tuple result = matrix_multiply_tuple(transform, p);

    assert(result.x == expected.x);
    assert(result.y == expected.y);
    assert(result.z == expected.z);

    free_matrix(transform);
}

int main()
{
    test_translation();
    printf("All tests passed.\n");
    return 0;
}