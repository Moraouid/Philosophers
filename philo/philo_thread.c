/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:11:46 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/05/27 02:59:06 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_life_loop(t_philo *philo)
{
	while (1)
	{
		if (check_death(philo))
			break ;
		if (take_forks(philo) == 1)
		{
			eat(philo);
			put_forks(philo);
		}
		sleep_and_think(philo);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0 || philo->id == philo->data->num_philosophers)
		usleep(1000);
	if (philo->data->num_philosophers == 1)
	{
		print_status(philo, "has taken a fork");
		usleep(philo->data->time_die * 1000);
		return (NULL);
	}
	philo_life_loop(philo);
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->num_philosophers)
		{
			pthread_mutex_lock(&data->meal_mutex);
			if (my_get_time() - data->philos[i++].last_meal > data->time_die)
			{
				pthread_mutex_lock(&data->print_mutex);
				data->stop = 1;
				printf("%ld %d %s\n", my_get_time() - data->start_time,
					data->philos->id, "died");
				pthread_mutex_unlock(&data->print_mutex);
				return (pthread_mutex_unlock(&data->meal_mutex), NULL);
			}
			pthread_mutex_unlock(&data->meal_mutex);
		}
		if (data->max_meals != -1 && all_philos_full(data))
			return (data->stop = 1, NULL);
	}
	return (NULL);
}

int	create_threads(t_philo *philos, t_data *data)
{
	int			i;
	pthread_t	monitor;

	data->start_time = my_get_time();
	i = 0;
	while (i < data->num_philosophers)
	{
		philos[i].last_meal = my_get_time();
		if (pthread_create(&(philos + i)->thread, NULL, philo_routine, &philos[i]))
			return (destroy_mutexes(data), free(philos), 0);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data))
		return (destroy_mutexes(data), free(philos), 0);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	return (1);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	free(data->forks);
}
