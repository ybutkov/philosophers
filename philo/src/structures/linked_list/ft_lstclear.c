/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:25:09 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/16 21:25:11 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list_internal.h"

void	ft_lst_clear(t_linked_list *lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*next;

	if (lst == NULL || del == NULL)
		return ;
	tmp = lst->head;
	while (tmp)
	{
		next = tmp->next;
		ft_delete_node(tmp, del);
		tmp = next;
	}
	lst->head = NULL;
	lst->last = NULL;
	lst->_size = 0;
}
