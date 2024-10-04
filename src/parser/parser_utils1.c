/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:41:46 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/04 14:43:45 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Function to count the number of elements in the array
int count_elements(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i] != NULL)
		i++;
	return (i);
}

