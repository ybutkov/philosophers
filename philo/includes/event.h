/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:52:20 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/17 14:17:48 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

# include "linked_list.h"
# include "structure.h"
# include <pthread.h>
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

typedef struct s_event_queue
{
	t_linked_list	*events;
	pthread_mutex_t	*mutex;
	int				is_someone_dead;

	void			(*push_event)(struct s_event_queue *queue,
			t_event *event);
	t_event			*(*pop_event)(struct s_event_queue *queue);
	void			(*free)(struct s_event_queue *queue);
}					t_event_queue;

t_event				*create_event(t_event_type event_type, int philo_id);
char				*get_event_type_string(t_event_type event_type);
t_event_queue		*create_event_queue(void);

#endif