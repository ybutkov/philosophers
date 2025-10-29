/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:29:13 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/29 12:15:09 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "printer.h"
#include "utils.h"
#include <fcntl.h>
#include <semaphore.h>
#include <stdlib.h>

void	set_up_initial_values(t_philo *philo, t_philo_data *philo_data,
		int id)
{
	philo->id = id;
	philo->last_meal_time = philo_data->start_time;
	philo->must_eat_times = philo_data->number_each_philosopher_must_eat;
	philo->time_to_die = philo_data->time_to_die;
	philo->print_semaphore = philo_data->print_semaphore;
	philo->start_time = philo_data->start_time;
	philo->forks = philo_data->forks;
	philo->ready_to_eat_sem = philo_data->ready_to_eat_sem;
	philo->dead_sem = philo_data->dead_sem;
}

void	free_philo(t_philo *philo)
{
	if (!philo)
		return ;
	if (philo->must_eat_times_sem != SEM_FAILED && philo->must_eat_times_sem)
		sem_close(philo->must_eat_times_sem);
	sem_unlink(philo->must_eat_times_sem_name);
	if (philo->meal_sem != SEM_FAILED && philo->meal_sem)
		sem_close(philo->meal_sem);
	sem_unlink(philo->meal_sem_name);
	if (philo->meal_sem_name)
		free(philo->meal_sem_name);
	if (philo->must_eat_times_sem_name)
		free(philo->must_eat_times_sem_name);
	free(philo);
}

char	*build_sem_name(char *base, int base_len, int id)
{
	char	*sem_name;
	char	*id_str;

	id_str = ft_itoa(id);
	if (!id_str)
		return (NULL);
	sem_name = malloc(sizeof(char) * (base_len + ft_strlen(id_str) + 1));
	if (!sem_name)
		return (free(id_str), NULL);
	ft_memmove(sem_name, base, base_len);
	ft_memmove(sem_name + base_len, id_str, ft_strlen(id_str) + 1);
	free(id_str);
	return (sem_name);
}

long int	get_last_meal_time(t_philo *philo)
{
	long int	last_meal_time;

	sem_wait(philo->meal_sem);
	last_meal_time = philo->last_meal_time;
	sem_post(philo->meal_sem);
	return (last_meal_time);
}
