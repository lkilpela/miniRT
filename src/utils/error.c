/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:30:06 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/07 14:42:32 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

void	fatal_error(const char *str)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	check_file_extension(char *filename)
{
	char	*ext;
	char	*first_ext;
	int		len;

	len = ft_strlen(filename);
	if (len < 3 || ft_strcmp(filename + len - 3, ".rt") != 0)
		fatal_error("Invalid file extension. Expected filename ends '.rt'\n");
	first_ext = ft_strnstr(filename, ".rt", len);
	ext = ft_strrchr(filename, '.');
	if (first_ext != ext)
		fatal_error("Invalid file extension. Expected only one '.rt'\n");
}

int	check_open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}
