/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiholee <jiholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 13:49:51 by jiholee           #+#    #+#             */
/*   Updated: 2021/05/06 13:49:52 by jiholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

t_philos	*philos(void)
{
	static	t_philos philo;

	return (&philo);
}

t_table		*table(void)
{
	static	t_table	table;

	return (&table);
}

int			ft_atoi(char *str)
{
	int ret;
	int sign;
	int i;

	i = 0;
	ret = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	return (ret * sign);
}
