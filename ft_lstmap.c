/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 23:51:21 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/15 00:12:33 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*new_lst;

	if (lst == NULL || f == NULL)
		return (NULL);
	new_lst = NULL;
	while (lst != NULL)
	{
		new_node = ft_lstnew(lst->content);
		if (new_node == NULL)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_node);
		lst = lst->next;
	}
	return (new_lst);
}
/**
 * Check if the original list lst or the function f is NULL. 
 * If either is NULL, return NULL.
 * 
 * Initialize a new list new_lst to NULL.
 * 
 * Iterate over each node in the original list.
 * 
 * On each iteration, create a new node with the content being the result of 
 * applying f to the content of the current node.
 * 
 * If the creation of the new node fails, clear the new list and return NULL.
 * 
 * If the creation of the new node succeeds, add the new node to the end of the 
 * new list.
 * 
 * After the loop, return the new list.
 * 
 */