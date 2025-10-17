/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:19:01 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/17 13:44:57 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list_internal.h"

static void	set_methods(t_linked_list *list)
{
	list->add_back_node = ft_add_back_node;
	list->add_back_value = ft_add_back_value;
	list->add_front_node = ft_add_front_node;
	list->add_front_value = ft_add_front_value;
	list->insert_node_after = ft_insert_node_after;
	list->insert_value_after = ft_insert_value_after;
	list->iterate = ft_lst_iter;
	list->clear = ft_lst_clear;
	list->get_size = ft_get_size;
	list->free = ft_free_linked_list;
	list->pop = pop_head_from_list;
}

t_linked_list	*create_linked_list(void *content)
{
	t_list			*node;
	t_linked_list	*list;
	int				size;

	list = malloc(sizeof(t_linked_list));
	if (list == NULL)
		return (NULL);
	node = NULL;
	size = 0;
	if (content != NULL)
	{
		node = ft_lst_new(content);
		if (node == NULL)
			return (free(list), NULL);
		size = 1;
	}
	list->head = node;
	list->last = node;
	list->_size = size;
	set_methods(list);
	return (list);
}
