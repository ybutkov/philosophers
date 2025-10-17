/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:25:45 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/17 13:45:31 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_linked_list
{
	struct s_list	*head;
	struct s_list	*last;
	int				_size;

	void			(*add_back_node)(struct s_linked_list *lst,
			struct s_list *new);
	struct s_list	*(*add_back_value)(struct s_linked_list *lst,
			void *content);
	void			(*add_front_node)(struct s_linked_list *lst,
			struct s_list *new);
	struct s_list	*(*add_front_value)(struct s_linked_list *lst,
			void *content);
	void			(*insert_node_after)(struct s_list *node,
			struct s_list *new);
	t_list			*(*pop)(struct s_linked_list *lst);
	struct s_list	*(*insert_value_after)(struct s_list *node, void *content);
	void			(*iterate)(struct s_linked_list *lst, void (*f)(void *));
	void			(*clear)(struct s_linked_list *lst, void (*del)(void *));
	int				(*get_size)(struct s_linked_list *lst);
	void			(*free)(struct s_linked_list *lst, void (*del)(void *));
}					t_linked_list;

t_linked_list		*create_linked_list(void *content);

#endif