/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 14:12:26 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/31 16:55:00 by ybutkov          ###   ########.fr       */
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
# define SEM_PHILO_IS_DEAD_BASE "/philo_is_dead_"
# define SEM_PHILO_IS_DEAD_BASE_LEN 15
# define SEM_READY_EAT "/philo_ready_to_eat"
# define SEM_SOMEONE_DEAD "/philo_dead_sem"

# define ERROR_FORK_FAILED "Error: Fork failed"
# define ERROR_THREAD_IN_FORK_FAILED "Error: Thread in fork creation failed"
# define ERROR_INVALID_ARGUMENTS "Error: Invalid arguments"

# define STATUS_ALL_ALIVE 0
# define STATUS_SOMEONE_DIED 1
# define STATUS_PHILO_DIED 2
# define STATUS_THREAD_IN_FORK_FAILED 3

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
	sem_t		*dead_sem;

	void		(*free)(struct s_philo_data *data);
}				t_philo_data;

typedef struct s_philo
{
	int			id;
	int			time_to_die;
	long int	last_meal_time;
	int			must_eat_times;
	long int	start_time;
	sem_t		*is_dead_sem;
	char		*is_dead_sem_name;
	int			status_is_dead;
	sem_t		*meal_sem;
	char		*meal_sem_name;
	sem_t		*print_semaphore;
	sem_t		*forks;
	sem_t		*ready_to_eat_sem;
	sem_t		*dead_sem;

	void		(*take_forks)(struct s_philo *philo);
	void		(*put_forks_down)(struct s_philo *philo);
	void		(*set_last_meal_time)(struct s_philo *philo, long int time);
	long int	(*get_last_meal_time)(struct s_philo *philo);
	void		(*set_is_dead)(struct s_philo *philo, int status_dead);
	int			(*get_is_dead)(struct s_philo *philo);
	void		(*free)(struct s_philo *philo);
}				t_philo;

t_philo_data	*parse_arguments_to_philo_data(int argc, char *argv[]);
t_philo_data	*create_philo_data(int number_of_philosophers, int time_to_die,
					int time_to_eat, int time_to_sleep);
t_philo			*create_philo(t_philo_data *philo_data, int id);
void			philosopher_action(t_philo_data *philo_data, int id);

#endif