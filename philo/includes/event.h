/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:52:20 by ybutkov           #+#    #+#             */
/*   Updated: 2025/11/02 15:52:47 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

# include "linked_list.h"
# include <pthread.h>
# include <sys/types.h>

# define EVENT_TYPE_COUNT 9
# define TIME_PHILO_FORMAT_OUTPUT "%lu %d "
# define DELAY_BEFORE_START_MS 1000

typedef enum e_event_type
{
	EVENT_TYPE_NONE,
	EVENT_TYPE_FORK_TAKEN,
	EVENT_TYPE_LEFT_FORK_TAKEN,
	EVENT_TYPE_RIGHT_FORK_TAKEN,
	EVENT_TYPE_EATING,
	EVENT_TYPE_SLEEPING,
	EVENT_TYPE_THINKING,
	EVENT_TYPE_FULLY_EATEN,
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
	pthread_mutex_t	*dead_mutex;
	int				is_someone_dead;

	void			(*push_event)(struct s_event_queue *queue, t_event *event);
	t_event			*(*pop_event)(struct s_event_queue *queue);
	void			(*mark_someone_dead)(struct s_event_queue *queue);
	int				(*check_if_someone_dead)(struct s_event_queue *queue);
	void			(*free)(struct s_event_queue *queue);
}					t_event_queue;

typedef struct s_dispatcher_data
{
	int				is_running;
	int				number_of_philosophers;
	int				time_to_die;
	long int		start_time;
	t_event_queue	*event_queue;
}					t_dispatcher_data;

t_event				*create_event(t_event_type event_type, int philo_id);
char				*get_event_type_string(t_event_type event_type);
t_event_queue		*create_event_queue(void);
t_dispatcher_data	*create_dispatcher_data(int number_of_philosophers,
						int time_to_die, t_event_queue *event_queue);

#endif