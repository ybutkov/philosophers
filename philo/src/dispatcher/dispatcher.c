/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:12:22 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/19 14:54:50 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h>

void			print_event(t_event *event);

static long int	*init_time_eatings(int number_of_philosophers,
		int **already_eaten)
{
	long int	*time_eatings;
	long int	start_time;
	int			i;

	time_eatings = malloc(sizeof(long int) * number_of_philosophers);
	if (!time_eatings)
		return (NULL);
	i = 0;
	start_time = get_time_in_milliseconds();
	while (i < number_of_philosophers)
	{
		(*already_eaten)[i] = 0;
		time_eatings[i] = start_time;
		i++;
	}
	return (time_eatings);
}

static int	check_death(t_dispatcher_data *dispatcher_data,
		long int *time_eatings, int *already_eaten, int is_someone_dead_already)
{
	long int	border_time;
	int			i;
	int			eaten_count;

	if (is_someone_dead_already)
		return (1);
	border_time = get_time_in_milliseconds() - dispatcher_data->time_to_die;
	i = 0;
	eaten_count = 0;
	while (i < dispatcher_data->number_of_philosophers)
	{
		if (!already_eaten[i] && time_eatings[i] < border_time)
		{
			printf("%ld %d died\n", get_time_in_milliseconds(), i + 1);
			return (1);
		}
		eaten_count += already_eaten[i];
		i++;
	}
	if (eaten_count == dispatcher_data->number_of_philosophers)
		return (1);
	return (0);
}

void	*dispatcher_routine(void *arg)
{
	t_event_queue		*event_queue;
	t_dispatcher_data	*dispatcher_data;
	t_event				*event;
	long int			*time_eatings;
	int					*already_eaten;
	int					is_someone_dead;

	dispatcher_data = (t_dispatcher_data *)arg;
	event_queue = dispatcher_data->event_queue;
	already_eaten = malloc(sizeof(int)
			* dispatcher_data->number_of_philosophers);
	if (!already_eaten)
		return (NULL);
	time_eatings = init_time_eatings(dispatcher_data->number_of_philosophers,
			&already_eaten);
	is_someone_dead = 0;
	// printf("Dispatcher started\n");
	while (is_someone_dead == 0)
	{
		// add logic to check for death
		while (event_queue->events->get_size(event_queue->events) > 0)
		{
			is_someone_dead = check_death(dispatcher_data, time_eatings,
					already_eaten, is_someone_dead);
			if (is_someone_dead)
			{
				event_queue->mark_someone_dead(event_queue);
				// need to print all remaining events before death event ???
				break ;
			}
			event = event_queue->pop_event(event_queue);
			if (event->event_type == EVENT_TYPE_FULLY_EATEN)
				already_eaten[event->philo_id - 1] = 1;
			else
				print_event(event);
			is_someone_dead = check_death(dispatcher_data, time_eatings,
					already_eaten, is_someone_dead);
			if (is_someone_dead)
			{
				event_queue->mark_someone_dead(event_queue);
				// need to print all remaining events before death event ???
				break ;
			}
			if (event->event_type == EVENT_TYPE_EATING)
				time_eatings[event->philo_id - 1] = event->timestamp;
			free(event);
		}
		is_someone_dead = check_death(dispatcher_data, time_eatings,
				already_eaten, is_someone_dead);
		if (is_someone_dead)
			event_queue->mark_someone_dead(event_queue);
	}
	free(time_eatings);
	return (NULL);
}
