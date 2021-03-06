/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiholee <jiholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 13:48:56 by jiholee           #+#    #+#             */
/*   Updated: 2021/05/07 14:19:48 by jiholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	msg(t_philos *philo, int status, unsigned long timestamp)
{
	pthread_mutex_lock(&table()->m_msg);
	if (table()->dead || table()->num_philo == table()->eat)
	{
		pthread_mutex_unlock(&table()->m_msg);
		return ;
	}
	if (status == EAT)
	{
		printf("%ld %d is eating\n", timestamp, philo->nbr);
		philo->eat++;
		if (philo->eat == table()->must_eat)
			table()->eat++;
	}
	else if (status == TAKEN)
		printf("%ld %d has taken a fork\n", timestamp, philo->nbr);
	else if (status == SLEEP)
		printf("%ld %d is sleeping\n", timestamp, philo->nbr);
	else if (status == THINK)
		printf("%ld %d is thinking\n", timestamp, philo->nbr);
	else if (status == DEAD)
	{
		printf("%ld %d died\n", timestamp, philo->nbr);
		table()->dead = 1;
	}
	pthread_mutex_unlock(&table()->m_msg);
}

int		eat(t_philos *philo)
{
	pthread_mutex_lock(&table()->fork[philo->fork1]);
	if (table()->dead == 1)
		return (END);
	msg(philo, TAKEN, get_time() - table()->base_time);
	pthread_mutex_lock(&table()->fork[philo->fork2]);
	if (table()->dead == 1 || table()->eat == table()->num_philo)
		return (END);
	msg(philo, TAKEN, get_time() - table()->base_time);
	msg(philo, EAT, get_time() - table()->base_time);
	philo->last_eat = get_time();
	usleep(table()->time_to_eat * 1000);
	pthread_mutex_unlock(&table()->fork[philo->fork1]);
	pthread_mutex_unlock(&table()->fork[philo->fork2]);
	return (ALIVE);
}

int		sleep_philo(t_philos *philo)
{
	int cur;

	if (table()->dead || table()->eat == table()->num_philo)
	{
		return (END);
	}
	msg(philo, SLEEP, get_time() - table()->base_time);
	cur = get_time();
	while (get_time() - cur <= table()->time_to_sleep && !table()->dead)
		usleep(50);
	return (ALIVE);
}

int		think(t_philos *philo)
{
	if (table()->dead || table()->eat == table()->num_philo)
	{
		return (END);
	}
	msg(philo, THINK, get_time() - table()->base_time);
	usleep(200);
	return (ALIVE);
}
