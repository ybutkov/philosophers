/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 17:30:37 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/28 17:34:44 by ybutkov          ###   ########.fr       */
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

#endif