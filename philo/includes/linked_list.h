/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:25:45 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/16 21:37:56 by ybutkov          ###   ########.fr       */
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

	void			(*add_back_node)(struct s_linked_list **lst,
			struct s_list *new);
	struct s_list	*(*add_back_value)(struct s_linked_list **lst,
			void *content);
	void			(*add_front_node)(struct s_linked_list **lst,
			struct s_list *new);
	struct s_list	*(*add_front_value)(struct s_linked_list **lst,
			void *content);
	void			(*insert_node)(struct s_list *node, struct s_list *next);
	struct s_list	*(*insert_value)(struct s_list *node, void *content);
	void			(*iterate)(struct s_linked_list *lst, void (*f)(void *));
	void			(*clear)(struct s_linked_list *node, void (*del)(void *));
	int				(*get_size)(struct s_linked_list *lst);
}					t_linked_list;

#endif