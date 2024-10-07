/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:00:57 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/07 14:13:40 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

void	check_args(int argc, char **argv)
{
	if (argc != 2)
		fatal_error("Usage: ./minirt <scene.rt>\n");
	check_file_extension(argv[1]);
}

t_world	*create_scene(char *filename)
{
	t_world	*w;

	w = default_world();
	parse_scene(filename, w);
	print_world(w);
	return (w);
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
