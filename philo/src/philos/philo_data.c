/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:52:32 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/19 16:03:53 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

static void	free_philo_data(t_philo_data *data)
{
	int	i;

	if (!data)
		return ;
	free_and_set_null(&data->dispatcher);
	if (data->philosophers)
	{
		i = 0;
		while (i < data->number_of_philosophers)
			free_and_set_null(&data->philosophers[i++]);
		free_and_set_null(data->philosophers);
	}
	free(data);
}

t_philo_data	*create_philo_data(int number_of_philosophers,
		int time_to_die, int time_to_eat, int time_to_sleep,
		int number_of_times_each_philosopher_must_eat)
{
	t_philo_data	*data;

	data = malloc(sizeof(t_philo_data));
	if (!data)
		return (NULL);
	data->number_of_philosophers = number_of_philosophers;
	data->time_to_die = time_to_die;
	data->time_to_eat = time_to_eat;
	data->time_to_sleep = time_to_sleep;
	data->number_of_times_each_philosopher_must_eat
		= number_of_times_each_philosopher_must_eat;
	data->free = free_philo_data;
	return (data);
}


