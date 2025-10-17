/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:44:07 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/17 21:14:31 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include "philo.h"
#include "printer.h"
#include "utils.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

t_philo_data	*check_philo_data(t_philo_data *data)
{
	pthread_t	*philosopher;
	
	if (data->number_of_philosophers <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
	{
		return (free(data), NULL);
	}
	if (data->number_of_times_each_philosopher_must_eat == 0)
		return (free(data), NULL);
	data->dispatcher = malloc(sizeof(pthread_t));
	if (!data->dispatcher)
		return (free(data), NULL);
	data->philosophers = malloc(data->number_of_philosophers
			* sizeof(pthread_t *));
	if (!data->philosophers)
		return (free(data), free(data->dispatcher), NULL);
	int i = 0;
	while (i < data->number_of_philosophers)
	{
		philosopher = malloc(sizeof(pthread_t));
		// ADD FREE
		if (!philosopher)
			return (NULL);
		data->philosophers[i++] = philosopher;
	}
	return (data);
}

t_philo_data	*parse_arguments(int argc, char const *argv[])
{
	t_philo_data	*data;

	if (argc < 5 || argc > 6)
		return (NULL);
	data = malloc(sizeof(t_philo_data));
	if (!data)
		return (NULL);
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	return (check_philo_data(data));
}

int	create_threads(t_event_queue *event_queue, t_philo_data *data)
{
	t_philo	*philo;
	int		i;

	pthread_create(data->dispatcher, NULL, dispatcher_routine, event_queue);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		philo = create_philo(i + 1, data, event_queue);
		// ADD FREE
		if (!philo)
			return (1);
		pthread_create(data->philosophers[i], NULL, philosopher_routine,
			philo);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
		pthread_detach(*data->philosophers[i++]);
	pthread_detach(*data->dispatcher);
	return (0);
}

int	main(int argc, char const *argv[])
{
	t_event_queue	*event_queue;
	t_philo_data	*philo_data;

	philo_data = parse_arguments(argc, argv);
	if (!philo_data)
	{
		printf("%s", "Error: Invalid arguments\n");
		return (1);
	}
	event_queue = create_event_queue();
	if (!event_queue)
		return (free(philo_data), 1);
	create_threads(event_queue, philo_data);

	while (event_queue->is_someone_dead == 0)
		usleep(5000);
	return (0);
}
