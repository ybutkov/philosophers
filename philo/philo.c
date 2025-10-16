/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:44:07 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/16 16:03:49 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"
#include "printer.h"

int	main(int argc, char const *argv[])
{
	t_event	*event;

	(void)argc;
	(void)argv;
	event = create_event(EVENT_TYPE_EATING, 1);
	print_event(event);
	event = create_event(EVENT_TYPE_SLEEPING, 8);
	print_event(event);
	event = create_event(EVENT_TYPE_LEFT_FORK_TAKEN, 4);
	print_event(event);
	return (0);
}
