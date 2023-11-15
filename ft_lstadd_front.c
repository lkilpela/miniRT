/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 22:57:59 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/14 23:21:41 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new != NULL)
	{
		new->next = *lst;
		*lst = new;
	}
}
/**
 * t_list **lst is a pointer to the first node of the list.
 * 
 * t_list *new is the new node to be added to the list.
 * 
 * new->next = *lst; sets the next field of the new node to the current first 
 * node of the list.
 * 
 * *lst = new; sets the new node as the first node of the list.
 * 
 * This function adds the new node at the beginning of the list, 
 * effectively making it the new head of the list.
 * 
 */