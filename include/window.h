/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:27:07 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/26 08:55:08 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "MLX42/MLX42.h"
# include "error.h"

typedef struct s_window
{
	int			width;
	int			height;
	mlx_t		*mlx;
	mlx_image_t	*img;
}				t_window;

void		key_hook(mlx_key_data_t keydata, void *param);
t_window	create_window(int width, int height);
void		libmlx_error(const char *message, mlx_t *mlx);

#endif
