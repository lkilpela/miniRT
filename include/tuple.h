/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:38:03 by lkilpela          #+#    #+#             */
/*   Updated: 2024/10/07 14:33:43 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLE_H
# define TUPLE_H

typedef struct s_tuple //point
{
	float	x;
	float	y;
	float	z;
	float	w;
}				t_tuple;

/* TUPLE.C */
t_tuple	create_tuple(float x, float y, float z, float w);
t_tuple	point(float x, float y, float z);
t_tuple	vector(float x, float y, float z);

/* TUPLE_MATH.C */
t_tuple	add(t_tuple a, t_tuple b);
t_tuple	subtract(t_tuple p1, t_tuple p2);
t_tuple	multiply_by_epsilon(t_tuple t);
t_tuple	multiply_by_scalar(t_tuple t, float scalar);
t_tuple	divide(t_tuple a, t_tuple b);
float	dot(t_tuple a, t_tuple b);
float	magnitude(t_tuple v);
t_tuple	cross(t_tuple a, t_tuple b);
t_tuple	normalize(t_tuple v);
t_tuple	reflect(t_tuple in, t_tuple normal);
t_tuple	negate(t_tuple t);
t_tuple	normalize(t_tuple v);
double	adaptive_epsilon(t_tuple point);

#endif
