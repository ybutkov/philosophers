/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:12:22 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/17 20:54:22 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>

void	print_event(t_event *event);

void	*dispatcher_routine(void *arg)
{
	t_event_queue	*event_queue;
	long int		time;
	t_event			*event;

	event_queue = (t_event_queue *)arg;
	time = get_time_in_milliseconds();
	printf("Dispatcher started\n");
	while (event_queue->is_someone_dead == 0)
	{
		while (event_queue->events->get_size(event_queue->events) > 0)
		{
			event = event_queue->pop_event(event_queue);
			print_event(event);
			free(event);
		}
		if (get_time_in_milliseconds() - time > 5000)
		{
			event_queue->is_someone_dead = 1;
			break ;
		}
		usleep(1000);
	}
	printf("Dispatcher finished\n");
	return (NULL);
}
