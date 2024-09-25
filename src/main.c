#include "structs.h"


void key_hook(mlx_key_data_t keydata, void* param)
{
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(param);
}

/* void destroy_world(t_world *w)
{
    for (int i = 0; i < w->count; i++)
    {
        free(w->spheres[i].transform);
    }
    free(w->spheres);
    free(w);
} */

/* int main()
{
    
    // Initialize the MLX42 library
    mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "MLX42 Window", true);
    if (!mlx) {
        fprintf(stderr, "MLX42 initialization failed\n");
        return EXIT_FAILURE;
    }

    // Set the key hook
    mlx_key_hook(mlx, &key_hook, mlx);

    mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
    if (!img) {
        fprintf(stderr, "Failed to create image\n");
        return EXIT_FAILURE;
    }

    // Create the scene
    t_world *w = create_scene();
    if (!w) {
        fprintf(stderr, "Failed to create world\n");
        return EXIT_FAILURE;
    }


    // Create the camera
    t_camera c = camera(WIDTH, HEIGHT, M_PI / 3);
    setup_camera(&c);
    t_tuple from = point(0, 1.5, -5);
    t_tuple to = point(0, 1, 0);
    t_tuple up = vector(0, 1, 0);
    c.transform = view_transform(from, to, up);
    
    // Render the scene
    render(img, &c, w);

    // Display the image
    if (mlx_image_to_window(mlx, img, 0, 0) == -1) 
    {
        fprintf(stderr, "Failed to display image\n");
        return EXIT_FAILURE;
    }

    // Loop to keep the window open
    mlx_loop(mlx);

    // Cleanup
    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);

    destroy_world(w);
    return EXIT_SUCCESS;
} */



int main(void)
{
    //test_shapes();
    
    test_plane();
}
