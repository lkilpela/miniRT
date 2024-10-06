/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:30:40 by jlu               #+#    #+#             */
/*   Updated: 2024/10/05 17:29:02 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

bool is_valid_normal(t_tuple *normal)
{
	if (normal->x < -1 || normal->x > 1)
		return (false);
	if (normal->y < -1 || normal->y > 1)
		return (false);
	if (normal->z < -1 || normal->z > 1)
		return (false);
	return (true);
}
