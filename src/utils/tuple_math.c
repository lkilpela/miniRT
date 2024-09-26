/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:37:58 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/26 10:44:31 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Function to add two tuples
t_tuple	add(t_tuple a, t_tuple b)
{
	t_tuple	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	result.w = a.w + b.w;
	return (result);
}

// Function to subtract two tuples
t_tuple	subtract(t_tuple a, t_tuple b)
{
	t_tuple	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;
	return (result);
}

// Function to multiply a tuple by epsilon
t_tuple	multiply_by_epsilon(t_tuple t)
{
	t_tuple	result;

	result.x = t.x * EPSILON;
	result.y = t.y * EPSILON;
	result.z = t.z * EPSILON;
	result.w = t.w * EPSILON;
	return (result);
}

// Function to multiply a tuple by a scalar
t_tuple	multiply_by_scalar(t_tuple t, float scalar)
{
	t_tuple	result;

	result.x = t.x * scalar;
	result.y = t.y * scalar;
	result.z = t.z * scalar;
	result.w = t.w * scalar;
	return (result);
}

// Function to divide two tuples
t_tuple	divide(t_tuple a, t_tuple b)
{
	t_tuple	result;

	result.x = a.x / b.x;
	result.y = a.y / b.y;
	result.z = a.z / b.z;
	result.w = a.w / b.w;
	return (result);
}
