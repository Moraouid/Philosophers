/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 21:34:54 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/04/02 18:45:33 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_data(t_data *data, char **av)
{
	data->num_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	data->max_meals = ft_atoi(av[5]);
	else
	data->max_meals = -1;
	data->stop = 0;
}

long get_time(void)
{
	struct timeval time;
	long current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current_time);
}

void print_status(t_philo *philo, char *msg)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%ld Philosopher %d %s\n", get_time() - philo->data->start_time, philo->id, msg);
    pthread_mutex_unlock(&philo->data->print_mutex);
}


void mutex_initialization(t_data *data, t_philo *philos)
{
	int	i;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (!data->forks)
	{
		free(philos);
		return ;
	}
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->num_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->num_philosophers];
		philos[i].data = data;
		i++;
	}
    pthread_mutex_init(&data->print_mutex, NULL);
    pthread_mutex_init(&data->meal_mutex, NULL);	
}


void take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
}


void put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_status(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
}


void sleep_and_think(t_philo *philo)
{
	int sleep_time;
	 
	sleep_time = 0;
	print_status(philo, "is sleeping");
    while (sleep_time < philo->data->time_to_sleep * 1000)
    {
        usleep(500);
        pthread_mutex_lock(&philo->data->meal_mutex);
        if (philo->data->stop)
        {
            pthread_mutex_unlock(&philo->data->meal_mutex);
            return;
        }
        pthread_mutex_unlock(&philo->data->meal_mutex);
        sleep_time += 500;
    }
	print_status(philo, "is thinking");
}



void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	philo->last_meal_time = get_time();
	if (philo->id % 2 == 1)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->meal_mutex);
		if (philo->data->stop) 
		{
			pthread_mutex_unlock(&philo->data->meal_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->data->meal_mutex);

		take_forks(philo);
		eat(philo);
		pthread_mutex_lock(&philo->data->meal_mutex);
		if (philo->data->stop) 
		{
			pthread_mutex_unlock(&philo->data->meal_mutex);
			put_forks(philo);
			break;
		}
		pthread_mutex_unlock(&philo->data->meal_mutex);
		put_forks(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}


void *monitor_routine(void *arg)
{
	t_data *data = (t_data *)arg;
	int i;

	while (1)
	{
		i = 0;
		while (i < data->num_philosophers)
		{
			pthread_mutex_lock(&data->meal_mutex);
			if (get_time() - data->philos[i].last_meal_time > data->time_to_die)
			{
				print_status(&data->philos[i], "died");
				data->stop = 1;
				pthread_mutex_unlock(&data->meal_mutex);
				return NULL;
			}
			pthread_mutex_unlock(&data->meal_mutex);
			i++;
		}
		usleep(500);
	}
	return NULL;
}



void	create_threads(t_philo *philos, t_data *data)
{
	int	i;
	pthread_t monitor;

	data->start_time = get_time();
	data->philos = philos;
	i = 0;
	while (i < data->num_philosophers)
	{
		philos[i].last_meal_time = get_time();
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, data);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

void destroy_mutexes(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philosophers)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	free(data->forks);
}


int main(int ac, char **av)
{
	t_data data;
	t_philo *philos;

	if (!is_valid(ac, av))
	{
		printf("Error: Invalid argument\n");
		return 1;
	}
	init_data(&data, av);
	philos = malloc(sizeof(t_philo) * data.num_philosophers);
	if (!philos)
		return 1;
	mutex_initialization(&data, philos);
	create_threads(philos, &data);
	destroy_mutexes(&data);
	free(philos);
	return 0;
}
