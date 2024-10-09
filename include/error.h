/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:31:55 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/09 12:05:49 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

void	fatal_error(const char *str);
void	check_file_extension(char *filename);
int		check_open_file(const char *filename);
void	validate_tuple(char **str);
int		count_elements(char **array);
bool	is_valid_color_range(float value);
bool	is_valid_float(const char *str);
bool	is_valid_normal(t_tuple *normal);

#endif