/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 23:35:57 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/15 00:11:34 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (*lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}

/**
 * t_list *temp; is a temporary node used to keep track of the next node 
 * in the list.
 * 
 * if (*lst == NULL || del == NULL) return ; checks if the list or the delete 
 * function is NULL. If either is NULL, the function returns immediately.
 * 
 * The while loop iterates over each node in the list. On each iteration, 
 * it saves the next node in temp, deletes the current node with ft_lstdelone, 
 * and then moves to the next node with *lst = temp;.
 * 
 * After the loop, *lst = NULL; sets the list pointer to NULL, indicating that 
 * the list is now empty.
 * 
 */