/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:53:38 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/26 10:44:20 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Function to create a tuple
t_tuple	create_tuple(float x, float y, float z, float w)
{
	t_tuple	t;

	t.x = x;
	t.y = y;
	t.z = z;
	t.w = w;
	return (t);
}

// Function to create a point
t_tuple	point(float x, float y, float z)
{
	return (create_tuple(x, y, z, 1.0));
}

// Function to create a vector
t_tuple	vector(float x, float y, float z)
{
	return (create_tuple(x, y, z, 0.0));
}
