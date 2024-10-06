/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 22:51:54 by jlu               #+#    #+#             */
/*   Updated: 2024/10/06 22:54:30 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

t_coefficients	calculate_coefficients(t_ray r)
{
	t_coefficients coeffs;

	coeffs.a = (r.direction.x * r.direction.x) + (r.direction.z * r.direction.z);
	coeffs.b = 2 * r.origin.x * r.direction.x + 2 * r.origin.z * r.direction.z;
	coeffs.c = r.origin.x * r.origin.x + r.origin.z * r.origin.z - 1;
	return (coeffs);
}

void	find_intersection_points(float disc, t_coefficients coeffs, 
									float *t0, float *t1)
{
	*t0 = (-coeffs.b - sqrt(disc)) / (2 * coeffs.a);
	*t1 = (-coeffs.b + sqrt(disc)) / (2 * coeffs.a);
	if (*t0 > *t1)
		ft_swap(t0, t1);
}