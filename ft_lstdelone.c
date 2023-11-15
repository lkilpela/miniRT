/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 23:30:19 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/15 00:14:34 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
}
/**
 * if (lst == NULL || del == NULL) return; checks if either the node or the 
 * del function are NULL. If either is NULL, the function returns 
 * without doing anything.
 * 
 * del(lst->content); calls the del function to free the content of the node.
 * 
 * free(lst); frees the memory of the node itself.

 * 
 */