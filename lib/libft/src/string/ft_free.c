/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:33:15 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/06 14:26:37 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_free(char **t)
{
	int		i;

	i = 0;
	while (t[i] != 0)
	{
		free(t[i]);
		i++;
	}
	free(t);
}