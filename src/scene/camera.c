/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:28:32 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/07 23:42:43 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Function to compute the size of a pixel in the camera
static void	compute_pixel_size(t_camera *c)
{
	double	half_view;
	double	aspect;

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

// Function to create a new camera
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
