/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:51:50 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/17 16:42:37 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

typedef struct s_philo_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	pthread_t		*dispatcher;
	pthread_t		**philosophers;
}					t_philo_data;

typedef struct s_philo
{
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	t_event_queue	*event_queue;
}					t_philo;

t_philo				*create_philo(int id, t_philo_data *data,
						t_event_queue *event_queue);
void				*dispatcher_routine(void *arg);
void				*philosopher_routine(void *arg);

#endif