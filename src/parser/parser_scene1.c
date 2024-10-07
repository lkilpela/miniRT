/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scene1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:56:11 by jlu               #+#    #+#             */
/*   Updated: 2024/10/07 14:53:19 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

t_id	get_identifier(char *str)
{
	if (ft_strcmp(str, "A") == 0)
		return (AMBIENT);
	else if (ft_strcmp(str, "C") == 0)
		return (CAMERA);
	else if (ft_strcmp(str, "L") == 0)
		return (LIGHT);
	else if (ft_strcmp(str, "sp") == 0)
		return (SPHERE);
	else if (ft_strcmp(str, "pl") == 0)
		return (PLANE);
	else if (ft_strcmp(str, "cy") == 0)
		return (CYLINDER);
	else
		return (UNKNOWN);
}

int	is_valid_identifier(t_id id)
{
	return (id == AMBIENT || id == CAMERA || id == LIGHT
		|| id == SPHERE || id == PLANE || id == CYLINDER);
}
