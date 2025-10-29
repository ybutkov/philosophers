/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:52:32 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/29 12:12:46 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

static void	free_philo_data(t_philo_data *philo_data)
{
	if (!philo_data)
		return ;
	if (philo_data->forks != SEM_FAILED && philo_data->forks)
		sem_close(philo_data->forks);
	sem_unlink(SEM_FORK_BASE);
	if (philo_data->print_semaphore != SEM_FAILED
		&& philo_data->print_semaphore)
		sem_close(philo_data->print_semaphore);
	sem_unlink(SEM_PRINT_NAME);
	if (philo_data->ready_to_eat_sem != SEM_FAILED
		&& philo_data->ready_to_eat_sem)
		sem_close(philo_data->ready_to_eat_sem);
	sem_unlink(SEM_READY_EAT);
	if (philo_data->dead_sem != SEM_FAILED && philo_data->dead_sem)
		sem_close(philo_data->dead_sem);
	sem_unlink(SEM_SOMEONE_DEAD);
	free(philo_data);
}

t_philo_data	*create_philo_data(int number_of_philosophers,
		int time_to_die, int time_to_eat, int time_to_sleep)
{
	t_philo_data	*data;

	data = malloc(sizeof(t_philo_data));
	if (!data)
		return (NULL);
	data->number_of_philosophers = number_of_philosophers;
	data->time_to_die = time_to_die;
	data->time_to_eat = time_to_eat;
	data->time_to_sleep = time_to_sleep;
	data->number_each_philosopher_must_eat = -1;
	data->forks = NULL;
	data->print_semaphore = NULL;
	data->ready_to_eat_sem = NULL;
	data->start_time = get_time_in_milliseconds();
	sem_unlink(SEM_FORK_BASE);
	sem_unlink(SEM_PRINT_NAME);
	sem_unlink(SEM_READY_EAT);
	sem_unlink(SEM_SOMEONE_DEAD);
	data->free = free_philo_data;
	return (data);
}
