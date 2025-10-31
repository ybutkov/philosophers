/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_op_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:31:37 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/31 19:32:04 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_internal.h"

void	set_philo_is_dead(t_philo *philo, int status_dead)
{
	sem_wait(philo->is_dead_sem);
	philo->status_is_dead = status_dead;
	sem_post(philo->is_dead_sem);
}

int	get_philo_is_dead(t_philo *philo)
{
	int	status_is_dead;

	sem_wait(philo->is_dead_sem);
	status_is_dead = philo->status_is_dead;
	sem_post(philo->is_dead_sem);
	return (status_is_dead);
}
