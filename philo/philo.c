/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:44:07 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/23 16:19:29 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include "philo_init_internal.h"
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
	data->philos = malloc(data->number_of_philosophers * sizeof(pthread_t *));
	if (!data->philos)
		return (free(data), free(data->dispatcher), NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		philosopher = malloc(sizeof(pthread_t));
		if (!philosopher)
			return (NULL);
		data->philos[i++] = philosopher;
	}
	return (data);
}

static int	check_arguments_are_digits(int argc, char const *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static t_philo_data	*parse_arguments(int argc, char const *argv[])
{
	t_philo_data	*data;

	if (argc < 5 || argc > 6)
		return (NULL);
	if (!check_arguments_are_digits(argc - 1, &argv[1]))
		return (NULL);
	data = create_philo_data(ft_atoi(argv[1]), ft_atoi(argv[2]),
			ft_atoi(argv[3]), ft_atoi(argv[4]));
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	return (check_philo_data(data));
}

static int	create_threads(t_event_queue *event_queue, t_philo_data *data)
{
	t_philo				**philos;
	t_dispatcher_data	*dispatcher_data;
	pthread_mutex_t		**forks;
	int					i;

	forks = create_forks(data->number_of_philosophers);
	if (!forks)
		return (0);
	dispatcher_data = create_dispatcher_data(data->number_of_philosophers,
			data->time_to_die, event_queue);
	if (!dispatcher_data)
		return (0);
	pthread_create(data->dispatcher, NULL, dispatcher_routine, dispatcher_data);
	usleep(500);
	philos = create_philos(data, event_queue, forks);
	i = 0;
	pthread_join(*data->dispatcher, NULL);
	while (i < data->number_of_philosophers)
		pthread_join(*data->philos[i++], NULL);
	forks_destroy_and_free(philos, forks, data->number_of_philosophers);
	free(dispatcher_data);
	return (1);
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
	if (create_threads(event_queue, philo_data) == 0)
	{
		event_queue->free(event_queue);
		philo_data->free(philo_data);
		return (1);
	}
	philo_data->free(philo_data);
	event_queue->free(event_queue);
	return (0);
}
