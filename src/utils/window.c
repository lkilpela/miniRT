/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:21:02 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/09 17:27:24 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

void	libmlx_error(const char *message, mlx_t *mlx)
{
	ft_printf("%s: %s\n", message, mlx_strerror(mlx_errno));
	if (mlx)
		mlx_terminate(mlx);
	exit(EXIT_FAILURE);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(param);
}

static void	resize_callback(int width, int height, void *param)
{
	t_world		*w;

	w = (t_world *)param;
	w->window.width = width;
	w->window.height = height;
	mlx_delete_image(w->window.mlx, w->window.img);
	w->window.img = mlx_new_image(w->window.mlx, width, height);
	if (!w->window.img)
		libmlx_error("Failed to create new image", w->window.mlx);
	w->camera.hsize = width;
	w->camera.vsize = height;
	w->camera.pixel_size = (w->camera.half_width * 2) / width;
	render(w->window.img, w);
	if (mlx_image_to_window(w->window.mlx, w->window.img, 0, 0) < 0)
		libmlx_error("Failed to put image to window", w->window.mlx);
	ft_printf("Window resized to %d x %d\n", width, height);
}

static t_window	init_window(int width, int height, t_world *w)
{
	t_window	window;

	window.width = width;
	window.height = height;
	window.mlx = mlx_init(width, height, "miniRT", true);
	if (!window.mlx)
		libmlx_error("Failed to initialize MLX42", NULL);
	window.resize_callback = &resize_callback;
	mlx_resize_hook(window.mlx, window.resize_callback, w);
	return (window);
}

t_window	create_window(int width, int height, t_world *w)
{
	t_window	window;

	window = init_window(width, height, w);
	window.img = mlx_new_image(window.mlx, window.width, window.height);
	if (!window.img)
		libmlx_error("Failed to create window", window.mlx);
	return (window);
}
