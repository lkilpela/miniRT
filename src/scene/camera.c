#include "structs.h"

void	compute_pixel_size(t_camera c)
{
	double  half_view;
	double  aspect;

	half_view = tan(c.fov / 2);
	aspect = c.hsize / c.vsize;
	if (aspect >= 1)
	{
		c.half_width = half_view;
		c.half_height = half_view / aspect;
	}
	else
	{
		c.half_width = half_view * aspect;
		c.half_height = half_view;
	}
	c.pixel_size = (c.half_width * 2) / c.hsize;
}

// Formula to convert degrees (fov) to radians: degrees * PI / 180
t_camera	camera(double hsize, double vsize, double field_of_view)
{
	t_camera	c;

	c.hsize = hsize;
	c.vsize = vsize;
	c.fov = field_of_view * M_PI / 180;
	c.from = point(0, 0, 0);
	c.to = point(0, 0, 1);
	c.up = vector(0, 1, 0);
	c.transform = view_transform(c.from, c.to, c.up);
	c.half_width = 0;
	c.half_height = 0;
	c.pixel_size = 0;
	c.flag = false;
	compute_pixel_size(c);
	return (c);
}

t_ray ray_for_pixel(t_world *w, int px, int py)
{
    // Compute the offset from the edge of the canvas to the pixel's center
    double xoffset = (px + 0.5) * w->camera.pixel_size;
    double yoffset = (py + 0.5) * w->camera.pixel_size;

    // Compute the untransformed coordinates of the pixel in world space
    double world_x = w->camera.half_width - xoffset;
    double world_y = w->camera.half_height - yoffset;

    // Using the camera matrix, transform the canvas point and the origin
    t_matrix *inverse_transform = inverse(w->camera.transform);
	t_tuple pixel = matrix_multiply_tuple(inverse_transform, point(world_x, world_y, -1));
    t_tuple origin = matrix_multiply_tuple(inverse_transform, point(0, 0, 0));
    t_tuple direction = normalize(subtract(pixel, origin));
/* 	printf("Inverse_transform -- pixel -- origin -- direction\n");
	print_matrix(inverse_transform);
	print_tuple_p(pixel);
	print_tuple_p(origin);
	print_tuple_v(direction); */

    destroy_matrix(inverse_transform);
	t_ray r = ray(origin, direction);
    return (r);
}

// Convert t_color to uint32_t pixel
uint32_t color_to_pixel(t_color color)
{
    return ((int)(color.r * 255) << 24) | ((int)(color.g * 255) << 16)
		| ((int)(color.b * 255) << 8) | 0xFF;
}

// Create an image and set pixels
void    render(mlx_image_t *img, t_world *w)
{
	for (int y = 0; y < w->camera.vsize; y++)
	{
		for (int x = 0; x < w->camera.hsize; x++)
		{
			if (x >= w->camera.hsize || y >= w->camera.vsize)
			{
				ft_printf("Pixel coordinates out of bounds: (%d, %d)\n", x, y);
				continue;
			}            
			t_ray r = ray_for_pixel(w, x, y);
			t_color color = color_at(w, r, x, y);
			uint32_t pixel_color = color_to_pixel(color);
			mlx_put_pixel(img, x, y, pixel_color);
		}
	}
	
}
