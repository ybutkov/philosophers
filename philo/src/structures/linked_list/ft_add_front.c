/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_front.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:18:27 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/16 21:18:29 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list_internal.h"

void	ft_add_front_node(t_linked_list *lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	if (lst->head == NULL)
	{
		lst->head = new;
		lst->last = new;
	}
	else
	{
		new->next = lst->head;
		lst->head = new;
	}
	lst->_size++;
}

t_list	*ft_add_front_value(t_linked_list *lst, void *content)
{
	t_list	*new;

	if (lst == NULL)
		return (NULL);
	new = ft_lstnew(content);
	if (new == NULL)
		return (NULL);
	ft_add_front_node(lst, new);
	return (new);
}
