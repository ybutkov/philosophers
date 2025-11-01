/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:08:36 by ybutkov           #+#    #+#             */
/*   Updated: 2025/11/01 12:37:40 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_internal.h"
#include "philo.h"
#include "printer.h"
#include "utils.h"
#include <unistd.h>

int	sleep_untill_time_ms(t_philo *philo, long int target_time)
{
	long int	current_time;

	while (philo->get_is_dead(philo) == STATUS_ALL_ALIVE)
	{
		current_time = get_time_in_milliseconds();
		if (current_time >= target_time)
			return (1);
		usleep(1000);
	}
	return (0);
}

static void	*life_checker(void *arg)
{
	t_philo		*philo;
	long int	current_time;
	long int	last_meal_time;

	philo = (t_philo *)arg;
	while (philo->get_is_dead(philo) == STATUS_ALL_ALIVE)
	{
		current_time = get_time_in_milliseconds();
		last_meal_time = philo->get_last_meal_time(philo);
		if (current_time - last_meal_time >= (long int)philo->time_to_die)
		{
			philo->set_is_dead(philo, STATUS_PHILO_DIED);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}

static void	*dead_checker(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->dead_sem);
	philo->set_is_dead(philo, STATUS_SOMEONE_DIED);
	return (NULL);
}

t_philo	*init_philosopher(t_philo_data *philo_data, int id,
	pthread_t *life_thread, pthread_t *dead_thread)
{
	t_philo		*philo;

	philo = create_philo(philo_data, id);
	if (pthread_create(life_thread, NULL, life_checker, philo) != 0)
	{
		philo->free(philo);
		exit(STATUS_THREAD_IN_FORK_FAILED);
	}
	if (pthread_create(dead_thread, NULL, dead_checker, philo) != 0)
	{
		pthread_detach(*life_thread);
		philo->set_last_meal_time(philo, 0);
		usleep(1000);
		philo->free(philo);
		exit(STATUS_THREAD_IN_FORK_FAILED);
	}
	pthread_detach(*dead_thread);
	return (philo);
}

void	philosopher_action(t_philo_data *philo_data, int id)
{
	t_philo		*philo;
	int			status;
	pthread_t	life_thread;
	pthread_t	dead_thread;

	if (id == 1 && philo_data->number_of_philosophers == 1)
		one_philosopher(philo_data);
	philo = init_philosopher(philo_data, id, &life_thread, &dead_thread);
	print_event(philo, EVENT_TYPE_THINKING);
	// sleep_untill_time_ms(philo, philo->last_meal_time + 2 * id);
	philosopher_cycle(philo_data, philo);
	status = philo->get_is_dead(philo);
	pthread_join(life_thread, NULL);
	philo->free(philo);
	exit(status);
}
