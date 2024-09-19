#include "structs.h"

/*int main(void)
{
    //test_ray();
    //test_sphere_intersects_2p();
    //test_sphere_intersects_tangent();
    //test_sphere_intersects_raymiss();
    //test_sphere_intersects_rayinside();
   //test_sphere_behind_ray();
   //test_intersection();
   //test_aggregating_intersections();
    test_hit_all_positive();
    test_hit_some_negative();
    test_hit_all_negative();
    test_hit_lowest_nonnegative();

}*/

int main() {
    float valuesA[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    float valuesB[4][4] = {
        {16, 15, 14, 13},
        {12, 11, 10, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    };

    t_matrix *A = create_matrix(4, 4, valuesA);
    t_matrix *B = create_matrix(4, 4, valuesB);

    t_matrix *M = matrix_multiply_matrix(A, B);

    if (M) {
        for (int r = 0; r < M->y; r++) {
            for (int c = 0; c < M->x; c++) {
                printf("%f ", M->data[r][c]);
            }
            printf("\n");
        }
        destroy_matrix(M);
    }

    destroy_matrix(A);
    destroy_matrix(B);

    return 0;
}