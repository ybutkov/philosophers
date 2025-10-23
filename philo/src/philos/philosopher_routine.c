/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:53:57 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/23 15:36:18 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include "philo.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h>

void	sleep_untill_time_ms(t_event_queue *event_queue,
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
	target_time = philo->last_meal_time + philo->time_to_die - 10;
	sleep_untill_time_ms(event_queue, target_time);
}

static void	take_forks_and_eat(t_philo *philo, t_event_queue *event_queue)
{
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
}

void	*philosopher_routine(void *arg)
{
	t_philo			*philo;
	t_event_queue	*event_queue;

	philo = (t_philo *)arg;
	if (philo->left_fork == philo->right_fork)
		return (one_philosopher_routine(philo));
	event_queue = philo->event_queue;
	if (philo->id % 2 == 0)
		usleep(500);
	while (philo->must_eat_times != 0)
	{
		if (event_queue->check_if_someone_dead(event_queue))
			break ;
		philo->do_event_and_sleep(philo, EVENT_TYPE_THINKING, 0);
		take_forks_and_eat(philo, event_queue);
		if (event_queue->check_if_someone_dead(event_queue))
			break ;
		philo->do_event_and_sleep(philo, EVENT_TYPE_SLEEPING,
			philo->time_to_sleep);
	}
	philo->do_event_and_sleep(philo, EVENT_TYPE_FULLY_EATEN, 0);
	return (NULL);
}
