/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_wrapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:07:41 by lkilpela          #+#    #+#             */
/*   Updated: 2024/07/11 10:59:29 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

void initialize_window(int width, int height) {
    mlx_t *mlx = mlx_init(width, height, "miniRT", true);
    if (!mlx) {
        fprintf(stderr, "Failed to initialize MLX42\n");
        exit(EXIT_FAILURE);
    }
    mlx_loop(mlx);
}
