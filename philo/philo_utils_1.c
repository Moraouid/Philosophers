/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:44:26 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/05/24 16:54:14 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	for_philo_even(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	print_status(philo, "has taken a fork");
	return (1);
}

int	for_philo_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	print_status(philo, "has taken a fork");
	return (1);
}

void	init_data(t_data *data, char **av)
{
	data->num_philosophers = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->max_meals = -1;
	if (av[5])
		data->max_meals = ft_atoi(av[5]);
	data->stop = 0;
	data->time_to_think = 0;
	if (data->num_philosophers % 2 == 1)
		if (data->time_to_eat >= data->time_to_sleep)
			data->time_to_think = data->time_to_eat;
}

void	initialization_philos(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->num_philosophers];
		philos[i].data = data;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = 0;
		i++;
	}
}

int	initialization(t_data *data, t_philo *philos)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (!data->forks)
	{
		free(philos);
		return (0);
	}
	initialization_philos(philos, data);
	data->philos = philos;
	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i++], NULL))
			return (failling_destroy(data, i, 1), 0);
	}
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (failling_destroy(data, data->num_philosophers, 1), 0);
	if (pthread_mutex_init(&data->meal_mutex, NULL))
		return (failling_destroy(data, data->num_philosophers, 2), 0);
	return (1);
}
