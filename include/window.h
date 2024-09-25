/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:27:07 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/11 23:03:32 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <unistd.h>
# include <stdlib.h> // For exit and malloc

# define WINDOW_WIDTH 1080
# define WINDOW_HEIGHT 720

typedef struct s_window
{
	int				width;
	int				height;
	mlx_t			*mlx;
	mlx_image_t		*img;
}				t_window;

void        key_hook(mlx_key_data_t keydata, void* param);
t_window    create_window(int width, int height);
void        libmlx_error(const char *message, mlx_t *mlx);
#endif
