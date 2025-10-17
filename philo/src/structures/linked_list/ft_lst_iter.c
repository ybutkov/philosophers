/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_iter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:39:47 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/17 12:39:49 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list_internal.h"

void	ft_lst_iter(t_linked_list *lst, void (*f)(void *))
{
	t_list	*tmp;

	if (lst == NULL || f == NULL)
		return ;
	tmp = lst->head;
	while (tmp)
	{
		f(tmp->content);
		tmp = tmp->next;
	}
}
