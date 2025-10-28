/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:52:32 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/28 13:58:41 by ybutkov          ###   ########.fr       */
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
	sem_unlink(SEM_FORK_BASE);
	sem_unlink(SEM_PRINT_NAME);
	sem_unlink(SEM_READY_EAT);
	data->start_time = get_time_in_milliseconds();
	data->free = free_philo_data;
	return (data);
}
