/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 23:06:05 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/15 00:12:56 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/**
 * int i; declares a counter variable.
 * i = 0; initializes the counter to 0.
 * 
 * The while loop iterates over each node in the list. 
 * 
 * On each iteration, it increments the counter and moves to the next 
 * node with lst = lst->next;.
 * 
 * return (i); returns the total number of nodes in the list.
 * 
 */