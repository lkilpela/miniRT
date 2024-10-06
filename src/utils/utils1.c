/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlu <jlu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 23:11:57 by jlu               #+#    #+#             */
/*   Updated: 2024/10/06 23:13:29 by jlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

// Function to compare two floating-point numbers with a tolerance
bool	float_equals(float a, float b, float epsilon) 
{
    return fabs(a - b) < epsilon;
}

