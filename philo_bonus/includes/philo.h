/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 14:12:26 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/25 19:24:57 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <semaphore.h>

# define SEM_FORK_BASE "/philo_forks"
# define SEM_FORK_BASE_LEN 12
# define SEM_PRINT_NAME "/philo_printer"
# define EVENT_TYPE_COUNT 7
# define TIME_PHILO_FORMAT_OUTPUT "%lu %d "
# define SEM_MEAL_BASE "/philo_meal_"
# define SEM_MEAL_BASE_LEN 12

typedef enum e_event_type
{
	EVENT_TYPE_NONE,
	EVENT_TYPE_FORK_TAKEN,
	EVENT_TYPE_EATING,
	EVENT_TYPE_SLEEPING,
	EVENT_TYPE_THINKING,
	EVENT_TYPE_FULLY_EATEN,
	EVENT_TYPE_DIED
}				t_event_type;

typedef struct s_philo_data
{
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
	long int	start_time;
	sem_t		*forks;
	sem_t		*print_semaphore;

	void		(*free)(struct s_philo_data *data);
}				t_philo_data;

typedef struct s_philo
{
	int			id;
	int			time_to_die;
	int			time_last_meal_eat;
	sem_t		*meal_sem;
}				t_philo;

t_philo_data	*create_philo_data(int number_of_philosophers, int time_to_die,
					int time_to_eat, int time_to_sleep);

#endif