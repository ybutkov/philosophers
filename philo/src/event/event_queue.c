/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:56:57 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/22 19:56:58 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include "event_internal.h"
#include "linked_list.h"
#include "utils.h"

static void	free_event_queue(t_event_queue *queue)
{
	if (!queue)
		return ;
	if (queue->events)
		queue->events->free(queue->events, free);
	queue->events = NULL;
	if (queue->dead_mutex)
	{
		pthread_mutex_destroy(queue->dead_mutex);
		free(queue->dead_mutex);
		queue->dead_mutex = NULL;
	}
	free(queue);
}

static void	mark_someone_dead(t_event_queue *queue)
{
	pthread_mutex_lock(queue->dead_mutex);
	queue->is_someone_dead = 1;
	pthread_mutex_unlock(queue->dead_mutex);
}

static int	is_someone_dead(t_event_queue *queue)
{
	int	result;

	pthread_mutex_lock(queue->dead_mutex);
	result = queue->is_someone_dead;
	pthread_mutex_unlock(queue->dead_mutex);
	return (result);
}

t_event_queue	*create_event_queue(void)
{
	t_event_queue	*event_queue;

	event_queue = malloc(sizeof(t_event_queue));
	if (!event_queue)
		return (NULL);
	event_queue->events = create_linked_list(NULL);
	event_queue->dead_mutex = malloc(sizeof(pthread_mutex_t));
	if (!event_queue->events || !event_queue->dead_mutex)
	{
		event_queue->free(event_queue);
		return (NULL);
	}
	pthread_mutex_init(event_queue->dead_mutex, NULL);
	event_queue->is_someone_dead = 0;
	event_queue->free = free_event_queue;
	event_queue->push_event = push_event;
	event_queue->pop_event = pop_event;
	event_queue->mark_someone_dead = mark_someone_dead;
	event_queue->check_if_someone_dead = is_someone_dead;
	return (event_queue);
}
