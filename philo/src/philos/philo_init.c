/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:44:07 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/23 16:18:40 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_init_internal.h"
#include "event.h"
#include "utils.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t	**create_forks(int number_of_philosophers)
{
	pthread_mutex_t	**forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t *) * number_of_philosophers);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < number_of_philosophers)
	{
		forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!forks[i])
			return (NULL);
		pthread_mutex_init(forks[i++], NULL);
	}
	return (forks);
}

void	forks_destroy_and_free(t_philo **philos, pthread_mutex_t **forks,
		int number_of_philosophers)
{
	int	i;

	if (!forks)
		return ;
	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_mutex_destroy(forks[i]);
		free(forks[i]);
		free(philos[i]);
		i++;
	}
	free(forks);
	free(philos);
}

t_philo	**create_philos(t_philo_data *data, t_event_queue *event_queue,
		pthread_mutex_t **forks)
{
	t_forks_pair	fork_pair;
	t_philo			**philos;
	int				i;

	philos = malloc(sizeof(t_philo *) * data->number_of_philosophers);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		fork_pair.left_fork = forks[i];
		fork_pair.right_fork = forks[(i + 1) % data->number_of_philosophers];
		philos[i] = create_philo(i + 1, data, event_queue, fork_pair);
		if (!philos[i])
			return (0);
		pthread_create(data->philos[i], NULL, philosopher_routine, philos[i]);
		i++;
	}
	return (philos);
}
