/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:13:30 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/24 20:34:42 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include "printer.h"
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

static int	check_arguments_are_digits(int argc, char *argv[])
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

void	sleep_untill_time_ms(t_philo_data *philo_data, long int target_time)
{
	long int	current_time;

	(void)philo_data;
	while (1)
	{
		current_time = get_time_in_milliseconds();
		if (current_time >= target_time)
			break ;
		usleep(100);
	}
}


t_philo_data	*check_philo_data(t_philo_data *data)
{
	char	semaphore_name[16];
	int		i;
	char	*num;

	if (data->number_of_philosophers <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
	{
		return (free(data), NULL);
	}
	if (data->number_of_times_each_philosopher_must_eat == 0)
		return (free(data), NULL);
	i = 0;
	data->forks = malloc(data->number_of_philosophers * sizeof(sem_t *));
	if (!data->forks)
		return (free(data), NULL);
	while (i < data->number_of_philosophers)
	{
		memset(semaphore_name, 0, sizeof(semaphore_name));
		ft_memmove(semaphore_name, SEM_FORK_BASE, SEM_FORK_BASE_LEN);
		num = ft_itoa(i);
		ft_memmove(semaphore_name + SEM_FORK_BASE_LEN, num, ft_strlen(num));
		semaphore_name[SEM_FORK_BASE_LEN + ft_strlen(num)] = '\0';
		free(num);
		data->forks[i] = sem_open(semaphore_name, O_CREAT, 0644, 1);
		i++;
	}
	data->print_semaphore = sem_open(SEM_PRINT_NAME, O_CREAT, 0644, 1);
	return (data);
}

static t_philo_data	*parse_arguments(int argc, char *argv[])
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

void put_forks_down(t_philo_data *philo_data, int left, int right)
{
	sem_post(philo_data->forks[left]);
	sem_post(philo_data->forks[right]);
}

void take_forks(t_philo_data *philo_data, int first, int second, int id)
{
	sem_wait(philo_data->forks[first]);
	print_event(philo_data, id, EVENT_TYPE_FORK_TAKEN);
	sem_wait(philo_data->forks[second]);
	print_event(philo_data, id, EVENT_TYPE_FORK_TAKEN);
}

void	philosopher(t_philo_data *philo_data, int id)
{
	int			left;
	int			right;
	int			eat_count;
	long int	last_meal_time;
	long int	time;

	left = id;
	right = (id + 1) % philo_data->number_of_philosophers;
	eat_count = philo_data->number_of_times_each_philosopher_must_eat;
	if (id % 2 == 0)
		usleep(500);
	while (eat_count)
	{
		print_event(philo_data, id, EVENT_TYPE_THINKING);
		if (id % 2 == 0)
			take_forks(philo_data, left, right, id);
		else
			take_forks(philo_data, right, left, id);
		last_meal_time = get_time_in_milliseconds();
		print_event(philo_data, id, EVENT_TYPE_EATING);
		if (eat_count > 0)
			eat_count--;
		if (philo_data->time_to_eat <= philo_data->time_to_die)
			sleep_untill_time_ms(philo_data, last_meal_time + philo_data->time_to_eat);
		else
		{
			sleep_untill_time_ms(philo_data, last_meal_time + philo_data->time_to_die);
			print_event(philo_data, id, EVENT_TYPE_DIED);
			// ???
			put_forks_down(philo_data, left, right);
			exit(1);
		}
			
		// if (id == 0 && eat_count == 3)
		// 	exit(1);
		put_forks_down(philo_data, left, right);
		time = get_time_in_milliseconds();
		if (time + philo_data->time_to_sleep >= last_meal_time + philo_data->time_to_die)
		{
			sleep_untill_time_ms(philo_data, last_meal_time + philo_data->time_to_die);
			print_event(philo_data, id, EVENT_TYPE_DIED);
			exit(1);
		}
		print_event(philo_data, id, EVENT_TYPE_SLEEPING);
		sleep_untill_time_ms(philo_data, time + philo_data->time_to_sleep);
	}
	exit(0);
}

void	cleanup_and_exit(t_philo_data *philo_data)
{
	char	sem_name[32];

	for (int i = 0; i < philo_data->number_of_philosophers; i++)
	{
		sprintf(sem_name, "%s%d", SEM_FORK_BASE, i);
		sem_close(philo_data->forks[i]);
		sem_unlink(sem_name);
	}
	sem_close(philo_data->print_semaphore);
	sem_unlink(SEM_PRINT_NAME);
	philo_data->free(philo_data);
}

void reset_semaphores(int n)
{
	char	sem_name[32];

	for (int i = 0; i < n; i++)
	{
		sprintf(sem_name, "%s%d", SEM_FORK_BASE, i);
		sem_unlink(sem_name);
	}
	sem_unlink(SEM_PRINT_NAME);
}

int	main(int argc, char **argv)
{
	pid_t pids[200];
	int status;
	int i;
	t_philo_data *philo_data;

	reset_semaphores(20);

	philo_data = parse_arguments(argc, argv);
	if (!philo_data)
	{
		printf("%s", "Error: Invalid arguments\n");
		return (1);
	}

	for (i = 0; i < philo_data->number_of_philosophers; i++)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			philosopher(philo_data, i);
		}
		else if (pids[i] < 0)
		{
			cleanup_and_exit(philo_data);
			return (1);
		}
	}

	for (i = 0; i < philo_data->number_of_philosophers; i++)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			sem_wait(philo_data->print_semaphore);
			printf("==============================\n");
			printf("Philosopher %d died or encountered an error %d.\n", i, WEXITSTATUS(status));
			for (int j = 0; j < philo_data->number_of_philosophers; j++)
			{
				kill(pids[j], SIGKILL);
			}
			sem_post(philo_data->print_semaphore);
			break ;
		}
	}

	cleanup_and_exit(philo_data);
	return (0);
}