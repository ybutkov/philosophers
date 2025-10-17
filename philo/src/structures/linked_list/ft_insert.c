/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:34:32 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/17 12:37:01 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list_internal.h"

void	ft_insert_node_after(t_list *node, t_list *new)
{
	if (node == NULL || new == NULL)
		return ;
	new->next = node->next;
	node->next = new;
}

t_list	*ft_insert_value_after(t_list *node, void *content)
{
	t_list	*new;

	if (node == NULL)
		return (NULL);
	new = ft_lst_new(content);
	if (new == NULL)
		return (NULL);
	ft_insert_node_after(node, new);
	return (new);
}
