/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:46:48 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/16 14:50:04 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "event.h"

void	print_event(t_event *event)
{
	printf(get_event_type_string(event->event_type),
		event->timestamp, event->philo_id);
	printf("\n");
}
