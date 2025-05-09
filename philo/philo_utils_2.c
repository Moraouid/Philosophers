/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:28:22 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/04/26 10:28:46 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_to_field(t_data *data, int index, int flag)
{
	if (flag == 1)
	{
		while (0 <= --index)
			pthread_mutex_destroy(&data->forks[index]);
	}
	if (flag == 2)
		pthread_mutex_destroy(&data->print_mutex);
	free(data->forks);
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
