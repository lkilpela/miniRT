#include "structs.h"

t_camera	camera(double hsize, double vsize, double field_of_view)
{
	t_camera	c;

	c.hsize = hsize;
	c.vsize = vsize;
	c.fov = field_of_view;
    c.from = point(0, 0, 0);
    c.to = point(0, 0, 0);
    c.up = vector(0, 1, 0);
    c.half_width = 0;
    c.half_height = 0;
    c.pixel_size = 0;
    c.flag = false;
	c.transform = identity_matrix(4);
    return (c);
}
// Formula to convert degrees (fov) to radians: degrees * PI / 180
void    setup_camera(t_camera *camera)
{
	double  half_view;
	double  aspect;

	half_view = tan((camera->fov * M_PI / 180) / 2);
	aspect = camera->hsize / camera->vsize;
	if (aspect >= 1)
	{
		camera->half_width = half_view;
		camera->half_height = half_view / aspect;
	}
	else
	{
		camera->half_width = half_view * aspect;
		camera->half_height = half_view;
	}
	camera->pixel_size = (camera->half_width * 2) / camera->hsize;
	camera->transform = view_transform(camera->from, camera->to, camera->up);
}

t_ray ray_for_pixel(t_camera *camera, int px, int py)
{
    // Compute the offset from the edge of the canvas to the pixel's center
    double xoffset = (px + 0.5) * camera->pixel_size;
    double yoffset = (py + 0.5) * camera->pixel_size;

    // Compute the untransformed coordinates of the pixel in world space
    double world_x = camera->half_width - xoffset;
    double world_y = camera->half_height - yoffset;

    // Using the camera matrix, transform the canvas point and the origin
    t_matrix *inverse_transform = inverse(camera->transform);
	t_tuple a = point(world_x, world_y, -1);
	t_tuple b = point(camera->from.x, camera->from.y, camera->from.z);
    t_tuple pixel = matrix_multiply_tuple(inverse_transform, a);
    t_tuple origin = matrix_multiply_tuple(inverse_transform , b);
    t_tuple direction = normalize(subtract(pixel, origin));

    destroy_matrix(inverse_transform);
	t_ray r = ray(origin, direction);
    return (r);
}

// Convert t_color to uint32_t pixel
uint32_t color_to_pixel(t_color color)
{
    //return ((int)(color.r * 255) << 24) | ((int)(color.g * 255) << 16) |  ((int)(color.b * 255) << 8) | 0xFF;

	int r = (int)(color.r * 255);
    int g = (int)(color.g * 255);
    int b = (int)(color.b * 255);
    //uint8_t a = 0xFF; // Assuming full opacity

    // Pack the components into a uint32_t in RGBA order
    return ((uint32_t)(r << 24 | g << 16 | b << 8 | 255));
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
void    render(mlx_image_t *img, t_camera *camera, t_world *world)
{
	for (int y = 0; y < camera->vsize; y++)
	{
		for (int x = 0; x < camera->hsize; x++)
		{
			if (x >= camera->hsize || y >= camera->vsize)
			{
				fprintf(stderr, "Pixel coordinates out of bounds: (%d, %d)\n", x, y);
				continue;
			}            
			t_ray r = ray_for_pixel(camera, x, y);
			t_color color = color_at(world, r, x, y);
			uint32_t pixel_color = color_to_pixel(color);
			mlx_put_pixel(img, x, y, pixel_color);
		}
	}
	
}
