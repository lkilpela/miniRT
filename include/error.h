/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:31:55 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/26 07:46:51 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h>  // bool
# include <stdio.h>    // perror
# include <stdlib.h>   // exit, EXIT_FAILURE
# include <fcntl.h>    // open, O_RDONLY
# include <unistd.h>   // STDERR_FILENO
# include <libft.h> // ft_putstr_fd

void	fatal_error(const char *str);
void	check_file_extension(char *filename);
int     check_open_file(const char *filename);
void	validate_vector(char **str);
int     count_elements(char **array);
bool	is_valid_color_range(float value);

#endif