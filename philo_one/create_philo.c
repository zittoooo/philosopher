/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiholee <jiholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 13:48:47 by jiholee           #+#    #+#             */
/*   Updated: 2021/05/07 14:21:56 by jiholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*watch(void *phi)
{
	int			cur;
	t_philos	*philo;

	philo = (t_philos *)phi;
	while (!table()->dead)
	{
		if (table()->eat == table()->num_philo)
		{
			table()->dead = 1;
			break ;
		}
		cur = get_time();
		if ((cur - philo->last_eat) > table()->time_to_die)
		{
			msg(phi, DEAD, get_time() - table()->base_time);
			table()->dead = 1;
			break ;
		}
	}
	return (NULL);
}

void	*run(void *phi)
{
	pthread_t	monitor;
	t_philos	*philo;

	philo = (t_philos *)phi;
	if (philo->nbr % 2)
		usleep(100);
	pthread_create(&monitor, NULL, watch, philo);
	while (!table()->dead)
	{
		if (eat(philo))
			break ;
		else if (sleep_philo(philo))
			break ;
		else if (think(philo))
			break ;
	}
	pthread_join(monitor, NULL);
	return (NULL);
}

void	create_philo(void)
{
	int			i;
	t_philos	*philo;

	i = -1;
	philo = philos();
	if (!(philo = malloc(sizeof(t_philos) * table()->num_philo)))
		return ;
	while (++i < table()->num_philo)
	{
		philo[i].nbr = i + 1;
		if (i == 0)
			philo[i].fork1 = table()->num_philo - 1;
		else
			philo[i].fork1 = i - 1;
		philo[i].fork2 = i;
		philo[i].eat = 0;
		philo[i].last_eat = get_time();
		pthread_create(&philo[i].tid, NULL, run, &philo[i]);
	}
	check_dead();
	i = -1;
	while (++i < table()->num_philo)
		pthread_join(philo[i].tid, NULL);
	free(philo);
}

void	check_dead(void)
{
	int i;

	while (42)
	{
		usleep(300);
		if (table()->dead || table()->eat == table()->num_philo)
			break ;
	}
	i = -1;
	while (++i < table()->num_philo)
		pthread_mutex_unlock(&table()->fork[i]);
}
