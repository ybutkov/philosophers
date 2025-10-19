/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:44:07 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/19 19:09:55 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include "philo.h"
#include "printer.h"
#include "utils.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

t_philo_data	*check_philo_data(t_philo_data *data)
{
	pthread_t	*philosopher;
	int			i;

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
	i = 0;
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
	// check args are digits
	
	// if (argc == 6)
	// 	data = create_philo_data(ft_atoi(argv[1]), ft_atoi(argv[2]),
	// 			ft_atoi(argv[3]), ft_atoi(argv[4]), ft_atoi(argv[5]));
	// else
	// 	data = create_philo_data(ft_atoi(argv[1]), ft_atoi(argv[2]),
	// 			ft_atoi(argv[3]), ft_atoi(argv[4]), -1);
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
		// ADD FREE
		if (!forks[i])
			return (NULL);
		pthread_mutex_init(forks[i++], NULL);
	}
	return (forks);
}

int	create_threads(t_event_queue *event_queue, t_philo_data *data)
{
	t_philo				*philo;
	t_dispatcher_data	*dispatcher_data;
	pthread_mutex_t		**forks;
	t_forks_pair		fork_pair;
	int					i;

	forks = create_forks(data->number_of_philosophers);
	if (!forks)
		return (1);
	dispatcher_data = create_dispatcher_data(data->number_of_philosophers,
			data->time_to_die, event_queue);
	if (!dispatcher_data)
		return (1);
	pthread_create(data->dispatcher, NULL, dispatcher_routine, dispatcher_data);
	// for init dispatcher
	usleep(500);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		fork_pair.left_fork = forks[i];
		fork_pair.right_fork = forks[(i + 1) % data->number_of_philosophers];
		philo = create_philo(i + 1, data, event_queue, fork_pair);
		// ADD FREE
		if (!philo)
			return (1);
		pthread_create(data->philosophers[i], NULL, philosopher_routine, philo);
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
	// philo_data->
	return (0);
}
