#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600

void key_hook(mlx_key_data_t keydata, void* param)
{
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(param);
}

int main(void)
{
    // Initialize the MLX42 library
    mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "MLX42 Window", true);
    if (!mlx)
    {
        fprintf(stderr, "MLX42 initialization failed\n");
        return EXIT_FAILURE;
    }

    // Set the key hook
    mlx_key_hook(mlx, &key_hook, mlx);

    // Set a basic color (red) on the window
    mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
    uint32_t* pixels = (uint32_t*)img->pixels;
    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            pixels[y * WIDTH + x] = 0xFF0000FF; // Red color in ARGB format
        }
    }
    mlx_image_to_window(mlx, img, 0, 0);

    // Loop to keep the window open
    mlx_loop(mlx);

    // Cleanup
    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);

    return EXIT_SUCCESS;
}
