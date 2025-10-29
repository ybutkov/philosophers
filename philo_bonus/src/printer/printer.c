/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:46:48 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/29 14:16:47 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include <stdio.h>

char	*get_event_string(t_event_type event_type)
{
	const char	*event_strings[EVENT_TYPE_COUNT] = {"none",
		TIME_PHILO_FORMAT_OUTPUT "has taken a fork",
		TIME_PHILO_FORMAT_OUTPUT "is eating",
		TIME_PHILO_FORMAT_OUTPUT "is sleeping",
		TIME_PHILO_FORMAT_OUTPUT "is thinking",
		TIME_PHILO_FORMAT_OUTPUT "is full",
		TIME_PHILO_FORMAT_OUTPUT "died"};

	if (event_type <= EVENT_TYPE_NONE || event_type >= EVENT_TYPE_COUNT)
		return ("Unknown event type");
	return ((char *)event_strings[event_type]);
}

long int	print_event(t_philo *philo, t_event_type event_type)
{
	long int	time;

	sem_wait(philo->print_semaphore);
	time = get_time_in_milliseconds();
	printf(get_event_string(event_type), time - philo->start_time, philo->id);
	printf("\n");
	fflush(stdout);
	sem_post(philo->print_semaphore);
	return (time);
}
