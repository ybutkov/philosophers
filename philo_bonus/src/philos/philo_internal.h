/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:30:37 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/31 19:55:49 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_INTERNAL_H
# define PHILO_INTERNAL_H

# include "philo.h"

void		set_up_initial_values(t_philo *philo, t_philo_data *philo_data,
				int id);
void		free_philo(t_philo *philo);
char		*build_sem_name(char *base, int base_len, int id);
long int	get_last_meal_time(t_philo *philo);
int			get_philo_is_dead(t_philo *philo);
void		set_philo_is_dead(t_philo *philo, int status_dead);
void		philosopher_cycle(t_philo_data *philo_data, t_philo *philo);
void		one_philosopher(t_philo_data *philo_data);
int			sleep_untill_time_ms(t_philo *philo, long int target_time);
t_philo		*init_philosopher(t_philo_data *philo_data, int id,
				pthread_t *life_thread, pthread_t *dead_thread);

#endif