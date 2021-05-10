/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiholee <jiholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 13:49:36 by jiholee           #+#    #+#             */
/*   Updated: 2021/05/10 16:20:43 by jiholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	create_philo(void)
{
	int			i;
	t_philos	*philo;

	i = -1;
	if (!(philo = malloc(sizeof(t_philos) * table()->num_philo)))
		return ;
	while (++i < table()->num_philo)
	{
		philo[i].nbr = i + 1;
		philo[i].eat = 0;
		philo[i].last_eat = get_time();
		philo[i].pid = fork();
		if (philo[i].pid == 0)
			run(&philo[i]);
	}
	monitor(philo);
}

void	*watch(void *phi)
{
	int			cur;
	t_philos	*philo;

	philo = (t_philos *)phi;
	while (1)
	{
		cur = get_time();
		if ((cur - philo->last_eat) > table()->time_to_die)
		{
			msg(phi, DEAD, get_time() - table()->base_time);
			exit(1);
		}
	}
	return (NULL);
}

void	run(t_philos *philo)
{
	pthread_t	monitor;

	if (philo->nbr % 2)
		usleep(300);
	pthread_create(&monitor, NULL, watch, philo);
	while (1)
	{
		if (eat(philo))
			break ;
		else if (sleep_philo(philo))
			break ;
		else if (think(philo))
			break ;
	}
	pthread_join(monitor, NULL);
	exit(0);
}

void	monitor(t_philos *phi)
{
	int eat;
	int status;

	eat = 0;
	while (1)
	{
		if (waitpid(-1, &status, WNOHANG) <= 0)
			continue ;
		if (WEXITSTATUS(status) == 0)
		{
			eat++;
			if (eat == table()->num_philo)
				return ;
		}
		else if (WEXITSTATUS(status) == 1)
		{
			kill((pid_t)phi, SIGINT);
			return ;
		}
	}
}
