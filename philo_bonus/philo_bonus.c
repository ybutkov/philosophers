/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:13:30 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/29 19:26:35 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "printer.h"
#include "utils.h"
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// static int	check_arguments_are_digits(int argc, char *argv[])
// {
// 	int	i;
// 	int	j;

// 	i = 1;
// 	while (i < argc)
// 	{
// 		j = 0;
// 		while (argv[i][j])
// 		{
// 			if (argv[i][j] < '0' || argv[i][j] > '9')
// 				return (0);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// t_philo_data	*check_philo_data(t_philo_data *data)
// {
// 	if (data->number_of_philosophers <= 0 || data->time_to_die <= 0
// 		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
// 		|| data->number_each_philosopher_must_eat == 0)
// 		return (data->free(data), NULL);
// 	data->forks = sem_open(SEM_FORK_BASE, O_CREAT, 0644,
// 			data->number_of_philosophers);
// 	data->print_semaphore = sem_open(SEM_PRINT_NAME, O_CREAT, 0644, 1);
// 	data->ready_to_eat_sem = sem_open(SEM_READY_EAT, O_CREAT, 0644,
// 			data->number_of_philosophers / 2);
// 	if (data->forks == SEM_FAILED || data->print_semaphore == SEM_FAILED
// 		|| data->ready_to_eat_sem == SEM_FAILED)
// 		return (data->free(data), NULL);
// 	return (data);
// }

// static t_philo_data	*parse_arguments(int argc, char *argv[])
// {
// 	t_philo_data	*data;

// 	if (argc < 5 || argc > 6)
// 		return (NULL);
// 	if (!check_arguments_are_digits(argc - 1, &argv[1]))
// 		return (NULL);
// 	data = create_philo_data(ft_atoi(argv[1]), ft_atoi(argv[2]),
// 			ft_atoi(argv[3]), ft_atoi(argv[4]));
// 	if (argc == 6)
// 		data->number_each_philosopher_must_eat = ft_atoi(argv[5]);
// 	else
// 		data->number_each_philosopher_must_eat = -1;
// 	return (check_philo_data(data));
// }

int	get_index_pid(pid_t *pids, int size, pid_t pid)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pids[i] == pid)
			return (i);
		i++;
	}
	return (-1);
}

void	kill_them_all(pid_t *pids, int size)
{
	int	i;

	i = 0;
	while (i < size)
		kill(pids[i++], SIGKILL);
}

void	watch_dog(pid_t *pids, t_philo_data *philo_data)
{
	pid_t	pid;
	int		i;
	int		status;
	int		philo_index;
	t_philo	philo;

	i = 0;
	philo_index = 0;
	philo.print_semaphore = philo_data->print_semaphore;
	philo.start_time = philo_data->start_time;
	while (i < philo_data->number_of_philosophers)
	{
		pid = waitpid(-1, &status, 0);
		if (WIFEXITED(status) && (WEXITSTATUS(status) == 1
				|| WEXITSTATUS(status) == 2))
		{
			philo_index = get_index_pid(pids,
					philo_data->number_of_philosophers, pid);
			philo.id = philo_index + 1;
			while (i++ < philo_data->number_of_philosophers)
				sem_post(philo_data->dead_sem);
			if (WEXITSTATUS(status) == 1)
				print_event(&philo, EVENT_TYPE_DIED);
			else
				printf("%s\n", ERROR_THREAD_FAILED);
			sem_wait(philo_data->print_semaphore);
			break ;
		}
		i++;
	}
}

void	error_message_and_exit(char *message)
{
	printf("%s\n", message);
	exit(1);
}

int	main(int argc, char **argv)
{
	pid_t			pids[200];
	int				i;
	t_philo_data	*philo_data;

	philo_data = parse_arguments_to_philo_data(argc, argv);
	if (!philo_data)
		error_message_and_exit(ERROR_INVALID_ARGUMENTS);
	i = 0;
	while (i < philo_data->number_of_philosophers)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			philosopher_action(philo_data, i + 1);
		else if (pids[i] < 0)
		{
			kill_them_all(pids, philo_data->number_of_philosophers);
			philo_data->free(philo_data);
			error_message_and_exit(ERROR_FORK_FAILED);
		}
		i++;
	}
	watch_dog(pids, philo_data);
	philo_data->free(philo_data);
	return (0);
}
