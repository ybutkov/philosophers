/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:13:30 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/31 17:11:41 by ybutkov          ###   ########.fr       */
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

static int	get_index_pid(pid_t *pids, int size, pid_t pid)
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

static void	kill_them_all(pid_t *pids, int size)
{
	int	i;

	i = 0;
	while (i < size)
		kill(pids[i++], SIGKILL);
}

static void	someone_failed_or_died(pid_t *pids, t_philo_data *philo_data,
		pid_t pid, int status)
{
	int		philo_index;
	int		i;
	t_philo	philo;

	i = 0;
	philo.print_semaphore = philo_data->print_semaphore;
	philo.start_time = philo_data->start_time;
	philo_index = get_index_pid(pids, philo_data->number_of_philosophers, pid);
	philo.id = philo_index + 1;
	while (i++ < philo_data->number_of_philosophers)
		sem_post(philo_data->dead_sem);
	if (WEXITSTATUS(status) == STATUS_PHILO_DIED)
		print_event(&philo, EVENT_TYPE_DIED);
	else
		printf("%s\n", ERROR_THREAD_IN_FORK_FAILED);
	sem_wait(philo_data->print_semaphore);
}

static void	watch_dog(pid_t *pids, t_philo_data *philo_data)
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
		if (WIFEXITED(status) && (WEXITSTATUS(status) == STATUS_PHILO_DIED
				|| WEXITSTATUS(status) == STATUS_THREAD_IN_FORK_FAILED))
		{
			someone_failed_or_died(pids, philo_data, pid, status);
			break ;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	pid_t			pids[200];
	int				i;
	t_philo_data	*philo_data;

	philo_data = parse_arguments_to_philo_data(argc, argv);
	if (!philo_data)
		error_message_and_exit(ERROR_INVALID_ARGUMENTS, EXIT_FAILURE);
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
			error_message_and_exit(ERROR_FORK_FAILED, EXIT_FAILURE);
		}
		i++;
	}
	watch_dog(pids, philo_data);
	philo_data->free(philo_data);
	return (0);
}
