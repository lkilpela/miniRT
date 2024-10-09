/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:08:40 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/09 17:34:47 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Compute the offset from the edge of the canvas to the pixel's center
// Compute the untransformed coordinates of the pixel in world space
static t_tuple	calculate_given_pixel(t_camera *c, int px, int py)
{
	double	xoffset;
	double	yoffset;
	double	world_x;
	double	world_y;

	xoffset = (px + 0.5) * c->pixel_size;
	yoffset = (py + 0.5) * c->pixel_size;
	world_x = c->half_width - xoffset;
	world_y = c->half_height - yoffset;
	return (point(world_x, world_y, -1));
}

// Function to compute the ray for a given pixel
static t_ray	ray_for_pixel(t_world *w, int px, int py)
{
	t_matrix	inverse_transform;
	t_tuple		pixel;
	t_tuple		origin;
	t_tuple		direction;

	inverse_transform = inverse(w->camera.transform);
	pixel = matrix_multiply_tuple(inverse_transform,
			calculate_given_pixel(&w->camera, px, py));
	origin = matrix_multiply_tuple(inverse_transform, point(0, 0, 0));
	direction = normalize(subtract(pixel, origin));
	return (ray(origin, direction));
}

// Convert t_color to uint32_t pixel
static uint32_t	color_to_pixel(t_color color)
{
	return (((int)(color.r * 255) << 24) | ((int)(color.g * 255) << 16)
		| ((int)(color.b * 255) << 8) | 0xFF);
}

// Function to compute the color for a given ray
static t_color	color_at(t_world *world, t_ray r)
{
	t_intersections	xs;
	t_intersection	*hit_p;
	t_color			result;
	t_computations	comps;

	xs = intersect_world(world, r);
	hit_p = hit(&xs);
	if (hit_p)
	{
		comps = prepare_computations(*hit_p, r);
		result = shade_hit(world, comps);
	}
	else
		result = color(0, 0, 0);
	free(xs.array);
	return (result);
}

// Create an image and set pixels
void	render(mlx_image_t *img, t_world *w)
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
		while (x < w->camera.hsize)
		{
			r = ray_for_pixel(w, x, y);
			color = color_at(w, r);
			pixel_color = color_to_pixel(color);
			mlx_put_pixel(img, x, y, pixel_color);
			x++;
		}
		y++;
	}
}
