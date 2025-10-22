/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:40:33 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/22 17:45:03 by ybutkov          ###   ########.fr       */
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

int	ft_get_size(t_linked_list *lst)
{
	if (lst == NULL)
		return (0);
	return (lst->_size);
}

void	ft_free_linked_list(t_linked_list *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	lst->clear(lst, del);
	free(lst);
}
