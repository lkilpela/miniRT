/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:30:06 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/06 23:09:02 by jlu              ###   ########.fr       */
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

bool	is_valid_float(const char *str)
{
	int	i;
	int	count;
	bool has_digits;

	i = 0;
	count = 0;
	has_digits = false;
	while(ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			has_digits = true;
		else if (str[i] == '.') 
		{
			if (count++ > 0)
				return (false);
		} 
		else
			return (false);
		i++;
	}
	return (has_digits);
}

void	validate_tuple(char **str)
{
	int	i;

	i = 0;
	if (!str)
		fatal_error("Null pointer provided for tuple\n");
	while (str[i])
	{
		if (!is_valid_float(str[i]))
			fatal_error("Invalid float number\n");
		i++;
	}
	if (i != 3)
		fatal_error("Invalid number of tuple\n");
}
