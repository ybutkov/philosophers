/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:13:30 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/25 19:26:48 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include "printer.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
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
	if (data->number_of_philosophers <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
	{
		return (free(data), NULL);
	}
	if (data->number_of_times_each_philosopher_must_eat == 0)
		return (free(data), NULL);
	data->forks = sem_open(SEM_FORK_BASE, O_CREAT, 0644,
			data->number_of_philosophers);
	if (!data->forks)
		return (free(data), NULL);
	data->print_semaphore = sem_open(SEM_PRINT_NAME, O_CREAT, 0644, 1);
	if (!data->print_semaphore)
	{
		sem_close(data->forks);
		sem_unlink(SEM_FORK_BASE);
		return (free(data), NULL);
	}
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

void put_forks_down(t_philo_data *philo_data)
{
	sem_post(philo_data->forks);
	sem_post(philo_data->forks);
}

void take_forks(t_philo_data *philo_data, int id)
{
	sem_wait(philo_data->forks);
	print_event(philo_data, id, EVENT_TYPE_FORK_TAKEN);
	sem_wait(philo_data->forks);
	print_event(philo_data, id, EVENT_TYPE_FORK_TAKEN);
}

void	*life_checker(void *arg)
{
	t_philo		philo;

	return (void *)0;
	philo = *(t_philo *)arg;
	while (1)
	{
		sem_wait(philo.meal_sem);
		printf("Checking philosopher %d\n", philo.id);
		if (get_time_in_milliseconds() - philo.time_last_meal_eat
			>= (long int)philo.time_to_die)
		{
			print_event(NULL, philo.id, EVENT_TYPE_DIED);
			exit(1);
		}
		sem_post(philo.meal_sem);
		usleep(500);
	}
}

void	philosopher(t_philo_data *philo_data, int id)
{
	int			eat_count;
	long int	last_meal_time;
	long int	time;
	char		sem_name[32];
	pthread_t	thread;
	t_philo		philo;

	printf("Philosopher %d started\n", id);
	philo.id = id;
	philo.time_to_die = philo_data->time_to_die;
	philo.time_last_meal_eat = philo_data->start_time;
	ft_memmove(sem_name, SEM_MEAL_BASE, SEM_MEAL_BASE_LEN);
	char *t = ft_itoa(id);
	ft_memmove(sem_name + SEM_MEAL_BASE_LEN, t, strlen(t) + 1);
	printf("Philosopher %d semaphore name: %s\n", id, sem_name);
	fflush(stdout);
	philo.meal_sem = sem_open(sem_name, O_CREAT, 0644, 1);

	pthread_create(&thread, NULL, life_checker, &philo);
	pthread_detach(thread);
	eat_count = philo_data->number_of_times_each_philosopher_must_eat;
	while (eat_count)
	{
		print_event(philo_data, id, EVENT_TYPE_THINKING);
		take_forks(philo_data, id);
		last_meal_time = print_event(philo_data, id, EVENT_TYPE_EATING);
		if (eat_count > 0)
			eat_count--;
		sem_wait(philo.meal_sem);
		philo.time_last_meal_eat = last_meal_time;
		sem_post(philo.meal_sem);
		if (philo_data->time_to_eat <= philo_data->time_to_die)
			sleep_untill_time_ms(philo_data, last_meal_time + philo_data->time_to_eat);
		else
		{
			sleep_untill_time_ms(philo_data, last_meal_time + philo_data->time_to_die);
			print_event(philo_data, id, EVENT_TYPE_DIED);
			put_forks_down(philo_data);
			exit(1);
		}
		put_forks_down(philo_data);
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
	// char	sem_name[32];

	// for (int i = 0; i < philo_data->number_of_philosophers; i++)
	// {
	// 	sprintf(sem_name, "%s%d", SEM_FORK_BASE, i);
	// 	sem_close(philo_data->forks[i]);
	// 	sem_unlink(sem_name);
	// }
	sem_close(philo_data->forks);
	sem_unlink(SEM_FORK_BASE);
	sem_close(philo_data->print_semaphore);
	sem_unlink(SEM_PRINT_NAME);
	philo_data->free(philo_data);
}

void reset_semaphores(void)
{
	// char	sem_name[32];

	// for (int i = 0; i < n; i++)
	// {
	// 	sprintf(sem_name, "%s%d", SEM_FORK_BASE, i);
	// 	sem_unlink(sem_name);
	// }
	sem_unlink(SEM_FORK_BASE);
	sem_unlink(SEM_PRINT_NAME);
}

int	main(int argc, char **argv)
{
	pid_t pids[200];
	int status;
	int i;
	t_philo_data *philo_data;

	reset_semaphores();

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

	i = 0;
	while (i < philo_data->number_of_philosophers)
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
		i++;
	}

	cleanup_and_exit(philo_data);
	return (0);
}
