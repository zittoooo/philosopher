/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiholee <jiholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 13:49:45 by jiholee           #+#    #+#             */
/*   Updated: 2021/05/07 15:40:35 by jiholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	msg(t_philos *philo, int status, unsigned long timestamp)
{
	sem_wait(table()->m_msg);
	if (status == EAT)
	{
		printf("%ld %d is eating\n", timestamp, philo->nbr);
		philo->eat++;
		if (philo->eat == table()->must_eat)
		{
			sem_post(table()->m_msg);
			sem_post(table()->fork);
			sem_post(table()->fork);
			exit(0);
		}
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
		exit(1);
	}
	sem_post(table()->m_msg);
}

int		eat(t_philos *philo)
{
	sem_wait(table()->fork);
	msg(philo, TAKEN, get_time() - table()->base_time);
	sem_wait(table()->fork);
	msg(philo, TAKEN, get_time() - table()->base_time);
	msg(philo, EAT, get_time() - table()->base_time);
	philo->last_eat = get_time();
	usleep(table()->time_to_eat * 1000);
	sem_post(table()->fork);
	sem_post(table()->fork);
	return (ALIVE);
}

int		sleep_philo(t_philos *philo)
{
	int cur;

	msg(philo, SLEEP, get_time() - table()->base_time);
	cur = get_time();
	while (get_time() - cur <= table()->time_to_sleep)
		usleep(1);
	return (ALIVE);
}

int		think(t_philos *philo)
{
	msg(philo, THINK, get_time() - table()->base_time);
	usleep(200);
	return (ALIVE);
}
