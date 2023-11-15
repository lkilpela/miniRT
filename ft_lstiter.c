/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 23:44:48 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/14 23:51:03 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst == NULL || f == NULL)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/**
 * if (lst == NULL || f == NULL) return; checks if either the list or the 
 * function are NULL. If either is NULL, the function returns without doing 
 * anything.
 * 
 * The while loop iterates over each node in the list. On each iteration, 
 * it applies the function f to the content of the current node with 
 * f(lst->content);, and then moves to the next node with lst = lst->next;.
 * 
 */