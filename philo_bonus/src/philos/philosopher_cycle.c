/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_cycle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:52:51 by ybutkov           #+#    #+#             */
/*   Updated: 2025/11/02 19:04:38 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_internal.h"
#include "printer.h"
#include "utils.h"
#include <unistd.h>

static int	wait_until_eat_time(t_philo *philo)
{
	long int	target_time;
	long int	last_meal_time;
	long int	current_time;

	last_meal_time = philo->get_last_meal_time(philo);
	if (last_meal_time == -1)
		return (1);
	target_time = last_meal_time + philo->time_to_die - 10;
	current_time = get_time_in_milliseconds();
	if (current_time >= target_time)
		return (1);
	return (sleep_untill_time_ms(philo, target_time));
}

void	one_philosopher(t_philo_data *philo_data)
{
	t_philo		*philo;
	long int	time;
	pthread_t	life_thread;
	pthread_t	dead_thread;

	philo = init_philosopher(philo_data, 1, &life_thread, &dead_thread);
	time = print_event(philo, EVENT_TYPE_THINKING);
	sleep_untill_time_ms(philo, time + philo->time_to_die);
	philo->free(philo);
	exit(STATUS_PHILO_DIED);
}

void	philosopher_cycle(t_philo_data *philo_data, t_philo *philo)
{
	int			eat_count;
	long int	last_meal_time;
	long int	time;

	eat_count = philo->must_eat_times;
	while (eat_count)
	{
		philo->take_forks(philo);
		if (philo->get_is_dead(philo) != STATUS_ALL_ALIVE)
			break ;
		last_meal_time = print_event(philo, EVENT_TYPE_EATING);
		philo->set_last_meal_time(philo, last_meal_time);
		if (eat_count > 0)
			eat_count--;
		if (sleep_untill_time_ms(philo, last_meal_time
				+ philo_data->time_to_eat) == 0)
			break ;
		philo->put_forks_down(philo);
		time = print_event(philo, EVENT_TYPE_SLEEPING);
		if (sleep_untill_time_ms(philo, time + philo_data->time_to_sleep) == 0)
			break ;
		print_event(philo, EVENT_TYPE_THINKING);
		if (wait_until_eat_time(philo) == 0)
			break ;
	}
}
