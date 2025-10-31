/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:20:08 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/31 19:32:48 by ybutkov          ###   ########.fr       */
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
	philo->set_is_dead = set_philo_is_dead;
	philo->get_is_dead = get_philo_is_dead;
}

t_philo	*create_philo(t_philo_data *philo_data, int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	set_up_initial_values(philo, philo_data, id);
	philo->meal_sem_name = build_sem_name(SEM_MEAL_BASE, SEM_MEAL_BASE_LEN, id);
	philo->is_dead_sem_name = build_sem_name(SEM_PHILO_IS_DEAD_BASE,
			SEM_PHILO_IS_DEAD_BASE_LEN, id);
	if (!philo->meal_sem_name || !philo->is_dead_sem_name)
		return (free_philo(philo), NULL);
	philo->meal_sem = sem_open(philo->meal_sem_name, O_CREAT, 0644, 1);
	philo->is_dead_sem = sem_open(philo->is_dead_sem_name,
			O_CREAT, 0644, 1);
	if (philo->meal_sem == SEM_FAILED
		|| philo->is_dead_sem == SEM_FAILED)
		return (free_philo(philo), NULL);
	sem_unlink(philo->meal_sem_name);
	sem_unlink(philo->is_dead_sem_name);
	set_up_philo_functions(philo);
	return (philo);
}
