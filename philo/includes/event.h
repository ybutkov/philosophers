/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:52:20 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/16 16:13:31 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

# include "structure.h"
# include <sys/types.h>

# define EVENT_TYPE_COUNT 8
# define TIME_PHILO_FORMAT_OUTPUT "%lu %d "

typedef enum e_event_type
{
	EVENT_TYPE_NONE,
	EVENT_TYPE_FORK_TAKEN,
	EVENT_TYPE_LEFT_FORK_TAKEN,
	EVENT_TYPE_RIGHT_FORK_TAKEN,
	EVENT_TYPE_EATING,
	EVENT_TYPE_SLEEPING,
	EVENT_TYPE_THINKING,
	EVENT_TYPE_DIED
}					t_event_type;

typedef struct s_event
{
	t_event_type	event_type;
	int				philo_id;
	long int		timestamp;
}					t_event;

t_event				*create_event(t_event_type event_type, int philo_id);
char				*get_event_type_string(t_event_type event_type);

#endif