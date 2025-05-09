/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 21:34:44 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/05/01 17:11:01 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_number(char *str)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+')
		i++;
	if (str[i] == '-' || str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		if (str[i] >= '0' && str[i] <= '9')
			num = num * 10 + (str[i] - '0');
		if (num > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	num;

	num = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}

int	is_valid(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (0);
	i = 1;
	while (i < ac)
	{
		if (is_valid_number(av[i]) == 0)
			return (0);
		if (ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}
