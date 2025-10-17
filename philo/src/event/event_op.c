/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:39:10 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/17 13:45:11 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"

void	push_event(t_event_queue *queue, t_event *event)
{
	pthread_mutex_lock(queue->mutex);
	queue->events->add_back_value(queue->events, event);
	pthread_mutex_unlock(queue->mutex);
}

t_event *pop_event(t_event_queue *queue)
{
	t_list	*popped_node;
	t_event	*event;

	pthread_mutex_lock(queue->mutex);
	popped_node = queue->events->pop(queue->events);
	pthread_mutex_unlock(queue->mutex);
	if (popped_node == NULL)
		return (NULL);
	event = (t_event *)popped_node->content;
	free(popped_node);
	return (event);
}
