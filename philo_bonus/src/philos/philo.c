/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:20:08 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/28 17:35:42 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_internal.h"
#include "printer.h"
#include "utils.h"
#include <fcntl.h>
#include <semaphore.h>
#include <stdlib.h>

static void	set_last_meal_time(t_philo *philo, long int time)
{
	sem_wait(philo->meal_sem);
	philo->last_meal_time = time;
	sem_post(philo->meal_sem);
}

static void	philo_take_forks(t_philo *philo)
{
	sem_wait(philo->ready_to_eat_sem);
	sem_wait(philo->forks);
	print_event(philo, EVENT_TYPE_FORK_TAKEN);
	sem_wait(philo->forks);
	print_event(philo, EVENT_TYPE_FORK_TAKEN);
}

static void	philo_put_forks_down(t_philo *philo)
{
	sem_post(philo->forks);
	sem_post(philo->forks);
	sem_post(philo->ready_to_eat_sem);
}

static void	set_up_philo_functions(t_philo *philo)
{
	philo->free = free_philo;
	philo->set_last_meal_time = set_last_meal_time;
	philo->get_last_meal_time = get_last_meal_time;
	philo->take_forks = philo_take_forks;
	philo->put_forks_down = philo_put_forks_down;
}

t_philo	*create_philo(t_philo_data *philo_data, int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	set_up_initial_values(philo, philo_data, id);
	philo->meal_sem_name = build_sem_name(SEM_MEAL_BASE, SEM_MEAL_BASE_LEN, id);
	philo->must_eat_times_sem_name = build_sem_name(SEM_MUST_EAT_BASE,
			SEM_MUST_EAT_BASE_LEN, id);
	if (!philo->meal_sem_name || !philo->must_eat_times_sem_name)
		return (free_philo(philo), NULL);
	philo->meal_sem = sem_open(philo->meal_sem_name, O_CREAT, 0644, 1);
	philo->must_eat_times_sem = sem_open(philo->must_eat_times_sem_name,
			O_CREAT, 0644, 1);
	if (philo->meal_sem == SEM_FAILED
		|| philo->must_eat_times_sem == SEM_FAILED)
		return (free_philo(philo), NULL);
	sem_unlink(philo->meal_sem_name);
	sem_unlink(philo->must_eat_times_sem_name);
	set_up_philo_functions(philo);
	return (philo);
}
