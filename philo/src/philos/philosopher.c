/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:53:57 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/22 19:58:51 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include "philo.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h>

static void	sleep_untill_time_ms(t_event_queue *event_queue,
		long int target_time)
{
	long int	current_time;

	while (event_queue->check_if_someone_dead(event_queue) == 0)
	{
		current_time = get_time_in_milliseconds();
		if (current_time >= target_time)
			break ;
		usleep(100);
	}
}

static void	*one_philosopher_routine(t_philo *philo)
{
	t_event_queue	*event_queue;

	event_queue = philo->event_queue;
	philo->take_left_fork(philo, event_queue);
	sleep_untill_time_ms(philo->event_queue, get_time_in_milliseconds()
		+ philo->time_to_die);
	philo->put_down_forks(philo);
	return (NULL);
}

static void	wait_until_eat_time(t_philo *philo, t_event_queue *event_queue)
{
	long int	target_time;

	if (philo->last_meal_time == -1)
		return ;
	target_time = philo->last_meal_time + philo->time_to_die
		- 10;
	sleep_untill_time_ms(event_queue, target_time);
}

void	*philosopher_routine(void *arg)
{
	t_philo			*philo;
	t_event_queue	*event_queue;

	philo = (t_philo *)arg;
	if (philo->left_fork == philo->right_fork)
		return (one_philosopher_routine(philo));
	event_queue = philo->event_queue;
	// printf("Philosopher %d started\n", philo->id);
	if (philo->id % 2 == 0)
		usleep(500);
	while (philo->must_eat_times != 0)
	{
		if (event_queue->check_if_someone_dead(event_queue))
			break ;
		philo->do_event_and_sleep(philo, EVENT_TYPE_THINKING, 0);
		wait_until_eat_time(philo, event_queue);
		if (philo->id % 2 == 0)
		{
			philo->take_left_fork(philo, event_queue);
			philo->take_right_fork(philo, event_queue);
		}
		else
		{
			philo->take_right_fork(philo, event_queue);
			philo->take_left_fork(philo, event_queue);
		}
		philo->do_event_and_sleep(philo, EVENT_TYPE_EATING, philo->time_to_eat);
		philo->put_down_forks(philo);
		philo->must_eat_times--;
		if (event_queue->check_if_someone_dead(event_queue))
			break ;
		philo->do_event_and_sleep(philo, EVENT_TYPE_SLEEPING,
			philo->time_to_sleep);
		if (event_queue->check_if_someone_dead(event_queue))
			break ;
	}
	philo->do_event_and_sleep(philo, EVENT_TYPE_FULLY_EATEN, 0);
	// free(philo);
	return (NULL);
}

static void	take_left_fork(t_philo *philo, t_event_queue *event_queue)
{
	pthread_mutex_lock(philo->left_fork);
	event_queue->push_event(event_queue, create_event(EVENT_TYPE_FORK_TAKEN,
			philo->id));
}

static void	take_right_fork(t_philo *philo, t_event_queue *event_queue)
{
	pthread_mutex_lock(philo->right_fork);
	event_queue->push_event(event_queue, create_event(EVENT_TYPE_FORK_TAKEN,
			philo->id));
}

static void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	if (philo->left_fork != philo->right_fork)
		pthread_mutex_unlock(philo->right_fork);
}

static void	event_and_sleep(t_philo *philo, t_event_type event_type,
		int sleep_time_ms)
{
	t_event	*event;

	event = create_event(event_type, philo->id);
	philo->event_queue->push_event(philo->event_queue, event);
	if (event_type == EVENT_TYPE_EATING)
		philo->last_meal_time = event->timestamp;
	sleep_untill_time_ms(philo->event_queue, event->timestamp + sleep_time_ms);
}

t_philo	*create_philo(int id, t_philo_data *data, t_event_queue *event_queue,
		t_forks_pair fork_pair)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->time_to_die = data->time_to_die;
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	philo->must_eat_times = data->number_of_times_each_philosopher_must_eat;
	philo->event_queue = event_queue;
	philo->left_fork = fork_pair.left_fork;
	philo->right_fork = fork_pair.right_fork;
	philo->last_meal_time = -1;
	philo->take_left_fork = take_left_fork;
	philo->take_right_fork = take_right_fork;
	philo->put_down_forks = put_down_forks;
	philo->do_event_and_sleep = event_and_sleep;
	return (philo);
}
