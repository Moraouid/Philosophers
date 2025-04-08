/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:11:46 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/04/08 23:37:27 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_life_loop(t_philo *philo)
{
	while (1)
	{
		if (check_die(philo))
			break ;
		if (take_forks(philo) == 1)
		{
			eat(philo);
			put_forks(philo);
		}
		if (check_die(philo))
			break ;
		sleep_and_think(philo);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	if (philo->id % 2 == 1)
		usleep(1000);
	if (philo->data->num_philosophers == 1)
	{
		print_status(philo, "has taken a fork");
		usleep(philo->data->time_to_die * 1000);
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
			if (get_time() - data->philos[i].last_meal_time > data->time_to_die)
			{
				print_status(&data->philos[i], "died");
				data->stop = 1;
				pthread_mutex_unlock(&data->meal_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->meal_mutex);
			i++;
		}
		if (data->max_meals != -1 && all_philos_full(data))
			return (data->stop = 1, NULL);
	}
	return (NULL);
}

void	create_threads(t_philo *philos, t_data *data)
{
	int			i;
	pthread_t	monitor;

	data->start_time = get_time();
	data->philos = philos;
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_lock(&data->meal_mutex);
		philos[i].last_meal_time = get_time();
		pthread_mutex_unlock(&data->meal_mutex);
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
