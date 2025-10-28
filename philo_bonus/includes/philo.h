/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 14:12:26 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/28 16:10:02 by ybutkov          ###   ########.fr       */
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
# define SEM_MUST_EAT_BASE "/philo_must_eat_"
# define SEM_MUST_EAT_BASE_LEN 16
# define SEM_READY_EAT "/philo_ready_to_eat"

# define ERROR_FORK_FAILED "Error: Fork failed"
# define ERROR_INVALID_ARGUMENTS "Error: Invalid arguments"

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
	int			number_each_philosopher_must_eat;
	long int	start_time;
	sem_t		*forks;
	sem_t		*ready_to_eat_sem;
	sem_t		*print_semaphore;

	void		(*free)(struct s_philo_data *data);
}				t_philo_data;

typedef struct s_philo
{
	int			id;
	int			time_to_die;
	long int	last_meal_time;
	int			must_eat_times;
	long int	start_time;
	sem_t		*must_eat_times_sem;
	char		*must_eat_times_sem_name;
	sem_t		*meal_sem;
	char		*meal_sem_name;
	sem_t		*print_semaphore;
	sem_t		*forks;
	sem_t		*ready_to_eat_sem;

	void		(*take_forks)(struct s_philo *philo);
	void		(*put_forks_down)(struct s_philo *philo);
	void		(*set_last_meal_time)(struct s_philo *philo, long int time);
	long int	(*get_last_meal_time)(struct s_philo *philo);
	void		(*free)(struct s_philo *philo);
}				t_philo;

t_philo_data	*create_philo_data(int number_of_philosophers, int time_to_die,
					int time_to_eat, int time_to_sleep);
t_philo			*create_philo(t_philo_data *philo_data, int id);
void			philosopher_action(t_philo_data *philo_data, int id);

#endif