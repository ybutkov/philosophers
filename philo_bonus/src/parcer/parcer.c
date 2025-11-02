/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:57:41 by ybutkov           #+#    #+#             */
/*   Updated: 2025/11/01 19:38:27 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include <fcntl.h>

static int	check_arguments_are_digits(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (i < argc)
	{
		j = 0;
		if ((argv[i][j] >= '0' && argv[i][j] <= '9') || argv[i][j] == '+')
			j++;
		else
			return (0);
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

static t_philo_data	*check_and_init_philo_data(t_philo_data *data)
{
	if (data->number_of_philosophers <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| data->number_each_philosopher_must_eat == 0)
		return (data->free(data), NULL);
	data->forks = sem_open(SEM_FORK_BASE, O_CREAT, 0644,
			data->number_of_philosophers);
	data->print_semaphore = sem_open(SEM_PRINT_NAME, O_CREAT, 0644, 1);
	data->ready_to_eat_sem = sem_open(SEM_READY_EAT, O_CREAT, 0644,
			data->number_of_philosophers / 2);
	data->dead_sem = sem_open(SEM_SOMEONE_DEAD, O_CREAT, 0644, 0);
	if (data->forks == SEM_FAILED || data->print_semaphore == SEM_FAILED
		|| data->ready_to_eat_sem == SEM_FAILED || data->dead_sem == SEM_FAILED)
		return (data->free(data), NULL);
	return (data);
}

t_philo_data	*parse_arguments_to_philo_data(int argc, char *argv[])
{
	t_philo_data	*data;

	if (argc < 5 || argc > 6)
		return (NULL);
	if (!check_arguments_are_digits(argc - 1, &argv[1]))
		return (NULL);
	data = create_philo_data(ft_atoi(argv[1]), ft_atoi(argv[2]),
			ft_atoi(argv[3]), ft_atoi(argv[4]));
	if (argc == 6)
		data->number_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->number_each_philosopher_must_eat = -1;
	return (check_and_init_philo_data(data));
}
