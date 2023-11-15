/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 22:40:33 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/14 23:22:25 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *) malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
/**
 * t_list *new_node; declares a pointer to a new t_list node.
 * 
 * new_node = malloc(sizeof(t_list)); allocates memory for the new node.
 * 
 * if (new_node == NULL) return (NULL); checks if the memory allocation 
 * was successful. If not, the function returns NULL.
 * 
 * new_node->content = content; assigns the content passed to the function to 
 * the content field of the new node.
 * 
 * new_node->next = NULL; initializes the next field of the new node to NULL, 
 * indicating that this is currently the last node in the list.
 * 
 * return (new_node); returns a pointer to the new node.
 * 
 * 
 */