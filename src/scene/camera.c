#include "structs.h"

void	compute_pixel_size(t_camera *c)
{
	double  half_view;
	double  aspect;

	half_view = tan(c->fov / 2);
	aspect = c->hsize / c->vsize;
	if (aspect >= 1)
	{
		c->half_width = half_view;
		c->half_height = half_view / aspect;
	}
	else
	{
		c->half_width = half_view * aspect;
		c->half_height = half_view;
	}
	c->pixel_size = (c->half_width * 2) / c->hsize;
}

t_camera	camera(t_world *w, double field_of_view, t_tuple from, t_tuple to)
{
	t_camera	c;

	c.hsize = w->window.width;
	c.vsize = w->window.height;
	c.fov = field_of_view * M_PI / 180;
	c.from = from;
	c.to = to;
	c.up = vector(0, 1, 0);
	c.transform = view_transform(c.from, c.to, c.up);
	c.half_width = 0;
	c.half_height = 0;
	c.pixel_size = 0;
	c.flag = true;
	compute_pixel_size(&c);
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
    t_matrix inverse_transform = inverse(w->camera.transform);
	t_tuple pixel = matrix_multiply_tuple(inverse_transform, point(world_x, world_y, -1));
    t_tuple origin = matrix_multiply_tuple(inverse_transform, point(0, 0, 0));
    t_tuple direction = normalize(subtract(pixel, origin));
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
	t_ray		r;
	t_color		color;
	uint32_t	pixel_color;
	int			x;
	int			y;

	y = 0;
	while (y < w->camera.vsize)
	{
		x = 0;
		while(x < w->camera.hsize)
		{
			r = ray_for_pixel(w, x, y);
			color = color_at(w, r, x, y);
			pixel_color = color_to_pixel(color);
			mlx_put_pixel(img, x, y, pixel_color);
			x++;
		}
		y++;
	}
}
