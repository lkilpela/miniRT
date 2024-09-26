/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:21:02 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/26 07:18:25 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

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

t_window	init_window(int width, int height)
{
	t_window	window;

	window.width = width;
	window.height = height;
	window.mlx = mlx_init(width, height, "miniRT", true);
	if (!window.mlx)
		libmlx_error("Failed to initialize MLX42", NULL);
	return (window);
}

t_window	create_window(int width, int height)
{
	t_window	window;

	window = init_window(width, height);
	window.img = mlx_new_image(window.mlx, window.width, window.height);
	if (!window.img)
		libmlx_error("Failed to create window", window.mlx);
	return (window);
}
