/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:51:50 by ybutkov           #+#    #+#             */
/*   Updated: 2025/11/02 13:51:51 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "event.h"
# include <pthread.h>

typedef struct s_forks_pair
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_forks_pair;

typedef struct s_philo_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	long int		time_for_start;
	pthread_t		*dispatcher;
	pthread_t		**philos;

	void			(*free)(struct s_philo_data *data);
}					t_philo_data;

typedef struct s_philo
{
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_times;
	long int		last_meal_time;
	long int		time_for_start;
	t_event_queue	*event_queue;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	void			(*take_left_fork)(struct s_philo *philo,
			t_event_queue *event_queue);
	void			(*take_right_fork)(struct s_philo *philo,
			t_event_queue *event_queue);
	void			(*put_down_forks)(struct s_philo *philo);
	void			(*do_event_and_sleep)(struct s_philo *philo,
			t_event_type event_type, int sleep_time_ms);
}					t_philo;

t_philo				*create_philo(int id, t_philo_data *data,
						t_event_queue *event_queue, t_forks_pair fork_pair);
t_philo_data		*create_philo_data(int number_of_philosophers,
						int time_to_die, int time_to_eat, int time_to_sleep);
void				*dispatcher_routine(void *arg);
void				*philosopher_routine(void *arg);

#endif