/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:34:45 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/04/04 14:39:30 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_philo t_philo;

typedef struct s_data
{
	int num_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int max_meals;
	int stop;
	pthread_mutex_t *forks;
	pthread_mutex_t print_mutex;
	pthread_mutex_t meal_mutex;
	long start_time;
	t_philo *philos;
	
} t_data;


typedef struct s_philo
{
	int id;
	int meals_eaten;
	long last_meal_time;
	t_data *data;
	pthread_t thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t meal_mutex;


} t_philo;

/* functions */
int ft_atoi(const char *str);
int is_valid(int ac, char **av);
void print_status(t_philo *philo, char *msg);
void take_forks(t_philo *philo);
void put_forks(t_philo *philo);
void eat(t_philo *philo);
void sleep_and_think(t_philo *philo);
long get_time(void);
int check_die(t_philo *philo);


#endif