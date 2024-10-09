/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:00:57 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/09 17:32:49 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

static void	check_args(int argc, char **argv)
{
	if (argc != 2)
		fatal_error("Usage: ./minirt <scene.rt>\n");
	check_file_extension(argv[1]);
}

static t_world	*create_scene(char *filename)
{
	t_world	*w;

	w = default_world();
	parse_scene(filename, w);
	return (w);
}

// Function to destroy a world
static void	destroy_world(t_world *w)
{
	int	i;

	if (!w)
		return ;
	if (w->objects)
	{
		i = 0;
		while (i < w->count)
		{
			free(w->objects[i]->material);
			free(w->objects[i]->object);
			free(w->objects[i]);
			i++;
		}
		free(w->objects);
	}
	free(w);
}

int	main(int argc, char **argv)
{
	t_world	*w;

	check_args(argc, argv);
	w = create_scene(argv[1]);
	if (!w)
		fatal_error("Failed to create scene");
	mlx_key_hook(w->window.mlx, &key_hook, w->window.mlx);
	render(w->window.img, w);
	if (mlx_image_to_window(w->window.mlx, w->window.img, 0, 0) < 0)
		libmlx_error("Failed to put image to window", w->window.mlx);
	mlx_loop(w->window.mlx);
	mlx_delete_image(w->window.mlx, w->window.img);
	mlx_terminate(w->window.mlx);
	destroy_world(w);
	return (EXIT_SUCCESS);
}
