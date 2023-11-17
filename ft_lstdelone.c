/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 23:30:19 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/17 09:16:24 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
		return ;
	if (lst->content != NULL)
		del(lst->content);
	free(lst);
}
/**
 * ft_lstdelone frees the content of the node using the del function and then 
 * frees the node itself. This is fine if the content of the node was 
 * dynamically allocated and needs to be freed. But if the content of the node 
 * wasn't dynamically allocated (for example, if it's a string literal or an 
 * integer), then trying to free it will cause undefined behavior.
 * 
 * To avoid this, you could modify ft_lstclear and ft_lstdelone to only free the 
 * content of the node if it's not NULL.
 * 
 * if (lst == NULL || del == NULL) return; checks if either the node or the 
 * del function are NULL. If either is NULL, the function returns 
 * without doing anything.
 * 
 * del(lst->content); calls the del function to free the content of the node.
 * 
 * free(lst); frees the memory of the node itself.

 * 
 */