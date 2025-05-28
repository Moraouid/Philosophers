/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:28:22 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/05/24 19:54:09 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	failling_destroy(t_data *data, int index, int flag)
{
	if (flag == 1 || flag == 2)
	{
		while (--index)
			pthread_mutex_destroy(&data->forks[index]);
	}
	if (flag == 2)
		pthread_mutex_destroy(&data->print_mutex);
	free(data->forks);
	free(data->philos);
}

long	my_get_time(void)
{
	struct timeval	time;
	long			current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current_time);
}
