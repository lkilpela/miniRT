#include "structs.h"

void	check_args(int argc, char **argv)
{
	if (argc != 2)
		fatal_error("Usage: ./minirt <scene.rt>\n");
	check_file_extension(argv[1]);
}

void destroy_world(t_world *w)
{
    for (int i = 0; i < w->count; i++)
    {
        free(w->object[i].transform);
    }
    free(w->object);
    free(w);
}

//int	main(int argc, char **argv)
int main()
{
    t_world *w; 

    //check_args(argc, argv);
    // Create the scene
    w = create_scene();
    if (!w) {
        fprintf(stderr, "Failed to create world\n");
        return EXIT_FAILURE;
    }
    // Create the camera
    t_camera c = camera(WIDTH, HEIGHT, M_PI / 3);
    setup_camera(&c);
    t_tuple from = point(0, 1.5, -5); // Camera position (view point)
    t_tuple to = point(0, 1, 0); // Camera direction (orientation vector)
    t_tuple up = vector(0, 1, 0); // Camera up vector
    c.transform = view_transform(from, to, up);

    // Set the key hook
    mlx_key_hook(w->window.mlx, &key_hook, w->window.mlx);

    // Render the scene
    render(w->window.img, &c, w);

    // Display the image
	if (mlx_image_to_window(w->window.mlx, w->window.img, 0, 0) < 0)
		libmlx_error("Failed to put image to window", w->window.mlx);

    // Loop to keep the window open
    mlx_loop(w->window.mlx);

    // Cleanup
    mlx_delete_image(w->window.mlx, w->window.img);
    mlx_terminate(w->window.mlx);

    destroy_world(w);
    return (EXIT_SUCCESS);
}



/* int main(void)
{
    //test_shapes();
    
    test_plane();
} */
