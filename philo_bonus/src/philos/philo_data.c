/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:52:32 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/24 17:26:40 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

static void	free_philo_data(t_philo_data *data)
{
	if (!data)
		return ;
	// ADD FREEING OF SEMAPHORES IF NEEDED
	free(data);
}

t_philo_data	*create_philo_data(int number_of_philosophers,
		int time_to_die, int time_to_eat, int time_to_sleep)
{
	t_philo_data	*data;

	data = malloc(sizeof(t_philo_data));
	if (!data)
		return (NULL);
	data->number_of_philosophers = number_of_philosophers;
	data->time_to_die = time_to_die;
	data->time_to_eat = time_to_eat;
	data->time_to_sleep = time_to_sleep;
	data->start_time = get_time_in_milliseconds();
	data->free = free_philo_data;
	return (data);
}
