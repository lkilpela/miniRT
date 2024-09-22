#include "structs.h"

void key_hook(mlx_key_data_t keydata, void* param)
{
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(param);
}

int main()
{
    // Initialize the MLX42 library
    mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "MLX42 Window", true);
    if (!mlx) {
        fprintf(stderr, "MLX42 initialization failed\n");
        return EXIT_FAILURE;
    }

    // Set the key hook
    mlx_key_hook(mlx, &key_hook, mlx);

    // Create a canvas
    t_canvas my_canvas = canvas(WIDTH, HEIGHT);

    // Define a sphere
    t_sphere sp = sphere();
    sp.material = material();
    sp.material.color = color(1, 0.2, 1);
    sp.material.ambient = 0.1;
    sp.material.diffuse = 0.9;
    sp.material.specular = 0.9;
    sp.material.shininess = 200.0;

    // Define a light source
    t_light light = point_light(point(-10, 10, -10), color(1, 1, 1));

    // Render the scene
    render(&my_canvas, &sp, &light);

    // Create an image and set pixels
    mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
    uint32_t* pixels = (uint32_t*)img->pixels;
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            pixels[y * WIDTH + x] = my_canvas.pixels[y * WIDTH + x];
        }
    }
    mlx_image_to_window(mlx, img, 0, 0);

    // Loop to keep the window open
    mlx_loop(mlx);

    // Cleanup
    free(my_canvas.pixels);
    destroy_matrix(sp.transform);
    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);

    return EXIT_SUCCESS;
}

/*int main(void)
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
    test_lighting();
}*/



