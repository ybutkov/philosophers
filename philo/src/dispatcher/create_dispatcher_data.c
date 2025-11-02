/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_dispatcher_data.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 13:41:11 by ybutkov           #+#    #+#             */
/*   Updated: 2025/11/02 16:42:28 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include "utils.h"
#include <stdlib.h>

t_dispatcher_data	*create_dispatcher_data(int number_of_philosophers,
		int time_to_die, t_event_queue *event_queue)
{
	t_dispatcher_data	*dispatcher_data;

	dispatcher_data = malloc(sizeof(t_dispatcher_data));
	if (!dispatcher_data)
		return (NULL);
	dispatcher_data->is_running = 1;
	dispatcher_data->number_of_philosophers = number_of_philosophers;
	dispatcher_data->time_to_die = time_to_die;
	dispatcher_data->event_queue = event_queue;
	dispatcher_data->start_time = get_time_in_milliseconds();
	return (dispatcher_data);
}
