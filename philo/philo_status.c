/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:17:07 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/04/08 17:58:19 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d %s\n", get_time() - philo->data->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (for_philo_even(philo) == 0)
			return (0);
	}
	else
	{
		if (for_philo_odd(philo) == 0)
			return (0);
	}
	return (1);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat(t_philo *philo)
{
	if (check_die(philo))
		return ;
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	if (check_die(philo))
		return ;
	print_status(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
}

void	sleep_and_think(t_philo *philo)
{
	if (check_die(philo))
		return ;
	print_status(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
	if (check_die(philo))
		return ;
	if (check_die(philo))
		return ;
	print_status(philo, "is thinking");
	usleep(philo->data->time_to_think * 1000);
}
