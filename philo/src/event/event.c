/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:12:01 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/19 19:29:18 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include "event_internal.h"
#include "utils.h"
#include "linked_list.h"

char	*get_event_type_string(t_event_type event_type)
{
	const char	*event_string[EVENT_TYPE_COUNT] = {"none",
		TIME_PHILO_FORMAT_OUTPUT "has taken a fork",
		TIME_PHILO_FORMAT_OUTPUT "has taken a left fork",
		TIME_PHILO_FORMAT_OUTPUT "has taken a right fork",
		TIME_PHILO_FORMAT_OUTPUT "is eating",
		TIME_PHILO_FORMAT_OUTPUT "is sleeping",
		TIME_PHILO_FORMAT_OUTPUT "is thinking",
		TIME_PHILO_FORMAT_OUTPUT "is full",
		TIME_PHILO_FORMAT_OUTPUT "died"};

	if (event_type <= EVENT_TYPE_NONE || event_type >= EVENT_TYPE_COUNT)
		return ("Unknown event type");
	return ((char *)event_string[event_type]);
}

t_event	*create_event(t_event_type event_type, int philo_id)
{
	t_event	*new_event;

	new_event = malloc(sizeof(t_event));
	if (!new_event)
		return (NULL);
	new_event->event_type = event_type;
	new_event->philo_id = philo_id;
	new_event->timestamp = get_time_in_milliseconds();
	return (new_event);
}

void	free_event_queue(t_event_queue *queue)
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
	if (!event_queue->events)
	{
		free(event_queue);
		return (NULL);
	}
	event_queue->dead_mutex = malloc(sizeof(pthread_mutex_t));
	if (!event_queue->dead_mutex)
	{
		event_queue->events->free(event_queue->events, free);
		free(event_queue);
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
