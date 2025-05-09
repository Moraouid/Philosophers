/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 21:34:54 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/04/29 18:15:08 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;

	if (is_valid(ac, av) == 0)
	{
		printf("Error: Invalid argument\n");
		return (1);
	}
	init_data(&data, av);
	philos = malloc(sizeof(t_philo) * data.num_philosophers);
	if (!philos)
		return (1);
	if (!initialization(&data, philos))
		return (1);
	if (!create_threads(philos, &data))
	{
		destroy_mutexes(&data);
		free(philos);
		return (1);
	}
	destroy_mutexes(&data);
	free(philos);
	return (0);
}
