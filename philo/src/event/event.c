/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:56:50 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/22 19:56:53 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include "utils.h"

char	*get_event_type_string(t_event_type event_type)
{
	const char	*event_strings[EVENT_TYPE_COUNT] = {"none",
		TIME_PHILO_FORMAT_OUTPUT "has taken a fork",
		TIME_PHILO_FORMAT_OUTPUT "has taken a left fork",
		TIME_PHILO_FORMAT_OUTPUT "has taken a right fork",
		TIME_PHILO_FORMAT_OUTPUT "is eating",
		TIME_PHILO_FORMAT_OUTPUT "is sleeping",
		TIME_PHILO_FORMAT_OUTPUT "is thinking",
		TIME_PHILO_FORMAT_OUTPUT "is full",
		TIME_PHILO_FORMAT_OUTPUT "died"};

	if (event_type <= EVENT_TYPE_NONE || event_type >= EVENT_TYPE_COUNT)
		return ("Unknown event type");
	return ((char *)event_strings[event_type]);
}

t_event	*create_event(t_event_type event_type, int philo_id)
{
	t_event	*new_event;

	new_event = malloc(sizeof(t_event));
	if (!new_event)
		return (NULL);
	new_event->event_type = event_type;
	new_event->philo_id = philo_id;
	new_event->timestamp = get_time_in_milliseconds();
	return (new_event);
}
