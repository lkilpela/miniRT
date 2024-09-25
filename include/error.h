/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:31:55 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/17 06:54:54 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

#include <stdlib.h> // exit
#include <unistd.h> // STDERR_FILENO
#include <fcntl.h> // open
#include <stdio.h>  // perror
#include <libft.h>
#include "MLX42/MLX42.h"

void	fatal_error(const char *str);
void	check_file_extension(char *filename);
int     check_open_file(const char *filename);
void	validate_vector(char **str);
int     count_elements(char **array);
bool	is_valid_color_range(float value);

#endif