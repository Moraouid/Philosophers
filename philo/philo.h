/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:34:45 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/05/01 15:47:19 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					num_philosophers;
	int					time_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_think;
	int					max_meals;
	int					stop;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		meal_mutex;
	long				start_time;
	t_philo				*philos;
}						t_data;

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	long				last_meal;
	t_data				*data;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		meal_mutex;
}						t_philo;

/* functions */
int						ft_atoi(const char *str);
int						is_valid(int ac, char **av);
int						take_forks(t_philo *philo);
int						check_die(t_philo *philo);
int						for_philo_even(t_philo *philo);
int						for_philo_odd(t_philo *philo);
int						all_philos_full(t_data *data);
int						check_die(t_philo *philo);
int						all_philos_full(t_data *data);
int						initialization(t_data *data, t_philo *philos);
int						create_threads(t_philo *philos, t_data *data);
void					destroy_mutexes(t_data *data);
void					print_status(t_philo *philo, char *msg);
void					initialization_philos(t_philo *philos, t_data *data);
void					destroy_to_field(t_data *data, int index, int flag);
void					put_forks(t_philo *philo);
void					eat(t_philo *philo);
void					sleep_and_think(t_philo *philo);
void					init_data(t_data *data, char **av);
long					my_get_time(void);

#endif