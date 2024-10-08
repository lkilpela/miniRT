/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:27:07 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/08 22:27:37 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

typedef struct s_world	t_world;
typedef struct s_window
{
	int			width;
	int			height;
	mlx_t		*mlx;
	mlx_image_t	*img;
	void		(*resize_callback)(int width, int height, void *param);
}				t_window;

void		key_hook(mlx_key_data_t keydata, void *param);
t_window	create_window(int width, int height, t_world *w);
void		libmlx_error(const char *message, mlx_t *mlx);

#endif
