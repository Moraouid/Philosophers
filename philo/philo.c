/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 21:34:54 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/04/08 23:23:26 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;

	if (!is_valid(ac, av))
	{
		printf("Error: Invalid argument\n");
		return (1);
	}
	init_data(&data, av);
	philos = malloc(sizeof(t_philo) * data.num_philosophers);
	if (!philos)
		return (1);
	mutex_initialization(&data, philos);
	create_threads(philos, &data);
	destroy_mutexes(&data);
	free(philos);
	return (0);
}
