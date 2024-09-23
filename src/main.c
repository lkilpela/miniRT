#include "structs.h"

void key_hook(mlx_key_data_t keydata, void* param)
{
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(param);
}

void print_float(float f)
{
    printf("%f\n", f);
}

void print_world(t_world *w)
{
    printf("World count: %d\n", w->count);
    for (int i = 0; i < w->count; i++)
    {
        printf("Sphere %d: \n", i);
        print_tuple(w->spheres[i].center);
        print_matrix(w->spheres[i].transform);
        print_color(w->spheres[i].material.color);
        print_float(w->spheres[i].material.ambient);
        print_float(w->spheres[i].material.diffuse);
        print_float(w->spheres[i].material.specular);
    }
}

void destroy_world(t_world *w)
{
    for (int i = 0; i < w->count; i++)
    {
        free(w->spheres[i].transform);
    }
    free(w->spheres);
    free(w);
}



int main()
{
    // Initialize the MLX42 library
    mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "MLX42 Window", true);
    if (!mlx) {
        fprintf(stderr, "MLX42 initialization failed\n");
        return EXIT_FAILURE;
    }
    mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
    if (!img) {
        fprintf(stderr, "Failed to create image\n");
        return EXIT_FAILURE;
    }

    // Create the scene
    t_world *w = default_world();
    if (!w) {
        fprintf(stderr, "Failed to create world\n");
        return EXIT_FAILURE;
    }
    //print_world(w);

        // Create the camera
    t_camera c = camera(WIDTH, HEIGHT, M_PI / 3);
    setup_camera(&c);
    t_tuple from = point(0, 1.5, -5);
    t_tuple to = point(0, 1, 0);
    t_tuple up = vector(0, 1, 0);
    c.transform = view_transform(from, to, up);
    //print_matrix(c.transform);

    // Set the key hook
    mlx_key_hook(mlx, &key_hook, mlx);

    // Debug print
    //printf("World count: %d\n", w->count);
    //printf("Sphere position: \n");
    //print_tuple(matrix_multiply_tuple(w->spheres[0].transform, (w->spheres[0].center)));
   // print_tuple(matrix_multiply_tuple(w->spheres[1].transform, (w->spheres[1].center)));
    //print_tuple(matrix_multiply_tuple(w->spheres[2].transform, (w->spheres[2].center)));
    //printf("MIDDLE: ");
    //print_tuple(matrix_multiply_tuple(w->spheres[3].transform, (w->spheres[3].center)));
    //print_tuple(matrix_multiply_tuple(w->spheres[4].transform, (w->spheres[4].center)));
    //print_tuple(matrix_multiply_tuple(w->spheres[5].transform, (w->spheres[5].center)));

    // Render the scene
    render(img, &c, w);
    //print_world(w);
    // Display the image
    mlx_image_to_window(mlx, img, 0, 0);

    // Loop to keep the window open
    mlx_loop(mlx);

    // Cleanup
    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);

    destroy_world(w);
    return EXIT_SUCCESS;
}

/*
int main(void)
{
    //test_sphere_intersects_2p();
    //test_sphere_intersects_tangent();
    //test_sphere_intersects_raymiss();
    //test_sphere_intersects_rayinside();
   //test_sphere_behind_ray();
   //test_intersection();
   //test_aggregating_intersections();
    //test_hit_all_positive();
    //test_hit_some_negative();
    //test_hit_all_negative();
    //test_hit_lowest_nonnegative();
    //test_myltiply_by_inverse_translation();
    //test_translation_doesnot_affect_vector();
    //test_scaling_applied_to_vector();
    // test_multiplying_by_inverse_scaling();
    //test_reflection_is_scaling_by_negative_value();
    //test_rotate_x_point();
    //test_rotate_y_point();
    //test_rotate_z_point();
    //test_shearing();
    //test_chaining_transformations();
    //test_ray();
    //test_sphere();
    //test_sphere_transformation();
    //test_normal_at();
    //test_material();
    //test_lighting();
    //test_world();
    //test_precomputations();
    //test_shading();
    //test_view_transformation();
    //test_setup_camera();
    test_render();
}*/



