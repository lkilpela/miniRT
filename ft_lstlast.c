/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 23:14:51 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/15 00:11:10 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/**
 * if (lst == NULL) return (NULL); checks if the list is empty. If it is, 
 * the function returns NULL.
 * 
 * The while loop iterates over each node in the list until it finds a node 
 * where the next field is NULL, which indicates that this is the last node 
 * in the list.
 * 
 * return (lst); returns the last node of the list.
 * 
 */