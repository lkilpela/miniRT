/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:28:21 by lkilpela          #+#    #+#             */
/*   Updated: 2024/09/19 10:27:45 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <MLX42/MLX42.h>
# include <libft.h>
# include <tuple.h>
# include <math.h>
# include <fcntl.h>  // open
# include <unistd.h> // close, read, write
# include <stdio.h>  // printf, perror
# include <stdlib.h> // malloc, free, exit
# include <string.h> // strerror

# define WINDOW_WIDTH 1366
# define WINDOW_HEIGHT 768

typedef struct s_ray
{
    t_tuple origin;
    t_tuple direction;
}               t_ray;

typedef struct s_sphere
{
    t_tuple center;
    float radius;
    int id;
}               t_sphere;

typedef struct s_intersections
{
    float t1;
    float t2;
    int count; // Number of intersections
}               t_intersections;


//void test_ray();
t_ray ray(t_tuple origin, t_tuple direction);
t_tuple position(t_ray r, float t);
void test_sphere_intersects_ray();
#endif
