/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:19:01 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/16 21:19:03 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list_internal.h"

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
		node = ft_lstnew(content);
		if (node == NULL)
			return (free(list), NULL);
		size = 1;
	}
	list->head = node;
	list->last = node;
	list->_size = size;
	return (list);
}
