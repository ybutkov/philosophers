/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:53:57 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/17 20:55:59 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include "philo.h"
#include <unistd.h>
#include <stdio.h>

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_event_queue	*events;

	philo = (t_philo *)arg;
	events = philo->event_queue;
	printf("Philosopher %d started\n", philo->id);
	while (events->is_someone_dead == 0)
	{
		usleep(1000);
		events->push_event(events, create_event(EVENT_TYPE_FORK_TAKEN, philo->id));
		usleep(1000);
		events->push_event(events, create_event(EVENT_TYPE_EATING, philo->id));
		usleep(2000);
		events->push_event(events, create_event(EVENT_TYPE_SLEEPING, philo->id));
		usleep(2000);
		events->push_event(events, create_event(EVENT_TYPE_LEFT_FORK_TAKEN, philo->id));
	}
	printf("Philosopher %d finished\n", philo->id);
	return (NULL);
}

t_philo	*create_philo(int id, t_philo_data *data, t_event_queue *event_queue)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->time_to_die = data->time_to_die;
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	philo->number_of_times_each_philosopher_must_eat
		= data->number_of_times_each_philosopher_must_eat;
	philo->event_queue = event_queue;
	return (philo);
}
