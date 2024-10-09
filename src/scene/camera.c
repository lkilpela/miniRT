/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:28:32 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/09 17:28:22 by lkilpela         ###   ########.fr       */
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

/* DEFINING VIEW TRANSFORMATION 
** Pretends the eye moves instead of the world
** - Specify where you want the eye to be in the scene (from)
** - Specify where you want the eye to look at (to)
** - Specify the direction of the up vector (up)
** - Return a view transformation matrix
*/
t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple		forward;
	t_tuple		left;
	t_tuple		true_up;
	t_matrix	orientation;
	t_matrix	combined;

	forward = normalize(subtract(to, from));
	left = cross(forward, normalize(up));
	true_up = cross(left, forward);
	orientation = identity_matrix();
	orientation.data[0][0] = left.x;
	orientation.data[0][1] = left.y;
	orientation.data[0][2] = left.z;
	orientation.data[1][0] = true_up.x;
	orientation.data[1][1] = true_up.y;
	orientation.data[1][2] = true_up.z;
	orientation.data[2][0] = -forward.x;
	orientation.data[2][1] = -forward.y;
	orientation.data[2][2] = -forward.z;
	combined = multiply_matrices(orientation,
			rotation(up, vector(0, 1, 0)));
	return (multiply_matrices(combined,
			translation(-from.x, -from.y, -from.z)));
}
