/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_internal.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:24:46 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/17 13:44:46 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_INTERNAL_H
# define LINKED_LIST_INTERNAL_H

# include "linked_list.h"
# include <stdlib.h>

void	ft_add_back_node(t_linked_list *lst, t_list *new);
t_list	*ft_add_back_value(t_linked_list *lst, void *content);
void	ft_add_front_node(t_linked_list *lst, t_list *new);
t_list	*ft_add_front_value(t_linked_list *lst, void *content);
void	ft_lst_clear(t_linked_list *lst, void (*del)(void *));
void	ft_delete_node(t_list *lst, void (*del)(void *));
void	ft_lst_iter(t_linked_list *lst, void (*f)(void *));
void	ft_lst_iter(t_linked_list *lst, void (*f)(void *));
t_list	*ft_lst_new(void *content);
int		ft_get_size(t_linked_list *lst);
void	ft_insert_node_after(t_list *node, t_list *new);
t_list	*ft_insert_value_after(t_list *node, void *content);
void	ft_free_linked_list(t_linked_list *lst, void (*del)(void *));
t_list	*pop_head_from_list(t_linked_list *lst);

#endif
