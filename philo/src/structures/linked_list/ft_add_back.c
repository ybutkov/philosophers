/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:18:35 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/16 21:18:38 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list_internal.h"

void	ft_add_back_node(t_linked_list *lst, t_list *new)
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
		lst->last->next = new;
		lst->last = new;
	}
	lst->_size++;
}

t_list	*ft_add_back_value(t_linked_list *lst, void *content)
{
	t_list	*new;

	if (lst == NULL)
		return ;
	new = ft_lstnew(content);
	if (new == NULL)
		return ;
	ft_add_back_node(lst, new);
}
