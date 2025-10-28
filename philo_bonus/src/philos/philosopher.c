/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:08:36 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/28 19:19:28 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include "printer.h"
#include <unistd.h>

static void	*life_checker(void *arg)
{
	t_philo		*philo;
	long int	current_time;
	long int	last_meal_time;

	philo = (t_philo *)arg;
	while (1)
	{
		last_meal_time = philo->get_last_meal_time(philo);
		current_time = get_time_in_milliseconds();
		if (current_time - last_meal_time >= (long int)philo->time_to_die)
		{
			philo->free(philo);
			/*
			 * Use _exit to avoid stdio flush races with other threads still
			 * printing. This prevents Helgrind data race reports on printf/flush.
			 */
			_exit(1);
		}
		usleep(1000);
	}
}

static void	sleep_untill_time_ms(long int target_time)
{
	long int	current_time;

	while (1)
	{
		current_time = get_time_in_milliseconds();
		if (current_time >= target_time)
			break ;
		usleep(1000);
	}
}

static void	wait_until_eat_time(t_philo *philo)
{
	long int	target_time;
	long int	last_meal_time;
	long int	current_time;

	last_meal_time = philo->get_last_meal_time(philo);
	if (last_meal_time == -1)
		return ;
	target_time = last_meal_time + philo->time_to_die - 10;
	current_time = get_time_in_milliseconds();
	if (current_time >= target_time)
		return ;
	sleep_untill_time_ms(target_time);
}

static void	run_life_checker_thread(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, life_checker, philo);
	pthread_detach(thread);
}

void	philosopher_action(t_philo_data *philo_data, int id)
{
	int			eat_count;
	long int	last_meal_time;
	long int	time;
	t_philo		*philo;

	philo = create_philo(philo_data, id);
	run_life_checker_thread(philo);
	eat_count = philo->must_eat_times;
	print_event(philo, EVENT_TYPE_THINKING);
	while (eat_count)
	{
		philo->take_forks(philo);
		last_meal_time = print_event(philo, EVENT_TYPE_EATING);
		if (eat_count > 0)
			eat_count--;
		philo->set_last_meal_time(philo, last_meal_time);
		sleep_untill_time_ms(last_meal_time + philo_data->time_to_eat);
		philo->put_forks_down(philo);
		time = print_event(philo, EVENT_TYPE_SLEEPING);
		sleep_untill_time_ms(time + philo_data->time_to_sleep);
		print_event(philo, EVENT_TYPE_THINKING);
		wait_until_eat_time(philo);
	}
	philo->free(philo);
	/* See note above: prefer _exit to avoid stdio flush in multi-threaded exit */
	_exit(0);
}
