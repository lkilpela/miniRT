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

void	ft_dlsadd_back(t_list **lst, t_list *new)
{
	t_list	*last;
	t_list	*prev = NULL;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_dlstlast(*lst);
		last->next = new;
		new->prev = last;
	}
}
