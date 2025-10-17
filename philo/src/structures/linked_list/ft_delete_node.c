/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:40:59 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/17 13:44:34 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list_internal.h"

void	ft_delete_node(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
}

t_list *pop_head_from_list(t_linked_list *lst)
{
	t_list	*popped_node;

	if (lst == NULL || lst->head == NULL)
		return (NULL);
	popped_node = lst->head;
	lst->head = lst->head->next;
	lst->_size--;
	if (lst->head == NULL)
		lst->last = NULL;
	popped_node->next = NULL;
	return (popped_node);
}
