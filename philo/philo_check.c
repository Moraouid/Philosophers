/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:16:24 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/04/22 15:05:43 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (0);
}

int	all_philos_full(t_data *data)
{
	int	i;
	int	full_count;

	i = 0;
	full_count = 0;
	pthread_mutex_lock(&data->meal_mutex);
	while (i < data->num_philosophers)
	{
		if (data->max_meals != -1 && data->philos[i].meals_eaten
			>= data->max_meals)
			full_count++;
		i++;
	}
	pthread_mutex_unlock(&data->meal_mutex);
	if (full_count == data->num_philosophers)
	{
		usleep(100);
		return (1);
	}
	return (0);
}
