/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlsadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:58:16 by lkilpela          #+#    #+#             */
/*   Updated: 2024/04/14 14:58:59 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_dlsadd_back(t_list **lst, t_list *new)
{
    t_list *last;

    if (*lst == NULL)
    {
        // If the list is empty, set the first node to be the new node
        *lst = new;
    }
    else
    {
        // Find the last node in the list
        last = ft_dlstlast(*lst);

        // Add the new node to the end of the list
        last->next = new;
        new->prev = last;
    }

    // Ensure the new node is the last node in the list
    new->next = NULL;
}
