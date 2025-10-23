/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_internal.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:12:23 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/23 16:15:15 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_INIT_INTERNAL_H
# define PHILO_INIT_INTERNAL_H

# include "philo.h"

t_philo_data	*check_philo_data(t_philo_data *data);
pthread_mutex_t	**create_forks(int number_of_philosophers);
void			forks_destroy_and_free(t_philo **philos,
					pthread_mutex_t **forks, int number_of_philosophers);
t_philo			**create_philos(t_philo_data *data, t_event_queue *event_queue,
					pthread_mutex_t **forks);

#endif
