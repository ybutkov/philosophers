/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:12:22 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/24 20:22:48 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include "printer.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h>

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

static int	is_finish_table(t_dispatcher_data *dispatcher_data,
		long int *time_eatings, int *already_eaten, int *is_finish)
{
	long int	border_time;
	int			i;
	int			eaten_count;

	if (*is_finish)
		return (*is_finish);
	border_time = get_time_in_milliseconds() - dispatcher_data->time_to_die;
	i = 0;
	eaten_count = 0;
	while (i < dispatcher_data->number_of_philosophers)
	{
		if (!already_eaten[i] && time_eatings[i] < border_time)
		{
			printf("%ld %d died\n", get_time_in_milliseconds()
				- dispatcher_data->start_time, i + 1);
			*is_finish = 1;
			return (*is_finish);
		}
		eaten_count += already_eaten[i];
		i++;
	}
	if (eaten_count == dispatcher_data->number_of_philosophers)
		*is_finish = 1;
	return (*is_finish);
}

static int	prepare_inner_data_philos(int number_philos,
		long int **time_eatings, int **already_eaten, int *is_someone_dead)
{
	*already_eaten = malloc(sizeof(int) * number_philos);
	if (!already_eaten)
		return (0);
	*time_eatings = init_time_eatings(number_philos, already_eaten);
	if (!time_eatings)
		return (free(already_eaten), 0);
	*is_someone_dead = 0;
	return (1);
}

static void	handle_events(t_dispatcher_data *dispatcher_data,
		int *already_eaten, long int *time_eatings, int *is_finish)
{
	t_event_queue	*event_queue;
	t_event			*event;

	event_queue = dispatcher_data->event_queue;
	while (event_queue->events->get_size(event_queue->events) > 0)
	{
		event_queue = dispatcher_data->event_queue;
		event = event_queue->pop_event(event_queue);
		if (event->event_type == EVENT_TYPE_FULLY_EATEN)
			already_eaten[event->philo_id - 1] = 1;
		else
			print_event(event, dispatcher_data->start_time);
		if (event->event_type == EVENT_TYPE_EATING)
			time_eatings[event->philo_id - 1] = event->timestamp;
		free(event);
		if (is_finish_table(dispatcher_data, time_eatings, already_eaten,
				is_finish))
		{
			event_queue->mark_someone_dead(event_queue);
			break ;
		}
	}
}

void	*dispatcher_routine(void *arg)
{
	t_dispatcher_data	*dispatcher_data;
	long int			*time_eatings;
	int					*already_eaten;
	int					is_finish;
	t_event_queue		*event_queue;

	dispatcher_data = (t_dispatcher_data *)arg;
	event_queue = dispatcher_data->event_queue;
	if (prepare_inner_data_philos(dispatcher_data->number_of_philosophers,
			&time_eatings, &already_eaten, &is_finish) == 0)
		return (NULL);
	while (is_finish == 0)
	{
		handle_events(dispatcher_data, already_eaten, time_eatings, &is_finish);
		if (is_finish_table(dispatcher_data, time_eatings, already_eaten,
				&is_finish))
			event_queue->mark_someone_dead(event_queue);
	}
	free(time_eatings);
	free(already_eaten);
	return (NULL);
}
