#include "structs.h"

t_camera	camera(double hsize, double vsize, double field_of_view)
{
	t_camera	c;

	c.hsize = hsize;
	c.vsize = vsize;
	c.fov = field_of_view;
	c.transform = identity_matrix(4);
	return (c);
}

void    setup_camera(t_camera camera)
{
	double  half_view;
	double  aspect;

	half_view = tan(camera.fov / 2);
	aspect = camera.hsize / camera.vsize;
	if (aspect >= 1)
	{
		camera.half_width = half_view;
		camera.half_height = half_view / aspect;
	}
	else
	{
		camera.half_width = half_view * aspect;
		camera.half_height = half_view;
	}
	camera.pixel_size = (camera.half_width * 2) / camera.hsize;
	camera.transform = view_transform(camera.from, camera.to, camera.up);
    print_camera(camera);

}

t_ray ray_for_pixel(t_camera camera, int px, int py)
{
    // Compute the offset from the edge of the canvas to the pixel's center
    double xoffset = (px + 0.5) * camera.pixel_size;
    double yoffset = (py + 0.5) * camera.pixel_size;

    // Compute the untransformed coordinates of the pixel in world space
    double world_x = camera.half_width - xoffset;
    double world_y = camera.half_height - yoffset;

    // Using the camera matrix, transform the canvas point and the origin
    t_matrix *inverse_transform = inverse(camera.transform);
    t_tuple pixel = matrix_multiply_tuple(inverse_transform, point(world_x, world_y, -1));
    t_tuple origin = matrix_multiply_tuple(inverse_transform , point(0, 0, 0));
    t_tuple direction = normalize(subtract(pixel, origin));
    destroy_matrix(inverse_transform);
    return ray(origin, direction);
}

// Convert t_color to uint32_t pixel
uint32_t color_to_pixel(t_color color)
{
    return ((int)(color.r * 255) << 24) | ((int)(color.g * 255) << 16) |  ((int)(color.b * 255) << 8) | 0xFF;
}

// Convert uint32_t pixel to t_color
t_color color_from_pixel(uint32_t pixel)
{
    t_color color;
    color.r = fmin(1.0, ((pixel >> 24) & 0xFF) / 255.0);
    color.g = fmin(1.0, ((pixel >> 16) & 0xFF)/ 255.0);
    color.b = fmin(1.0, ((pixel >> 8) & 0xFF) / 255.0);
    return color;
}

// Get the pixel color at (x, y) in an MLX42 image
uint32_t pixel_at(mlx_image_t *img, int x, int y)
{
    uint8_t* s = &img->pixels[(y * img->width + x) * BPP];
    return (s[0] << 24) | (s[1] << 16) | (s[2] << 8);
}

// Create an image and set pixels
void    render(mlx_image_t *img, t_camera camera, t_world *world)
{
    for (int y = 0; y < camera.flag; y++) 
    {
        for (int x = 0; x < camera.hsize; x++)
        {
            if (x >= camera.hsize || y >= camera.vsize)
            {
                fprintf(stderr, "Pixel coordinates out of bounds: (%d, %d)\n", x, y);
                continue;
            }            
            t_ray r = ray_for_pixel(camera, x, y);
            //printf(YELLOW "Ray: %f %f %f %f %f %f\n" RESET, r.origin.x, r.origin.y, r.origin.z, r.direction.x, r.direction.y, r.direction.z);
            t_color color = color_at(world, r);
            uint32_t pixel_color = color_to_pixel(color);
            mlx_put_pixel(img, x, y, pixel_color);
        }
    }
    
}
