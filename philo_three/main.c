/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiholee <jiholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 13:49:39 by jiholee           #+#    #+#             */
/*   Updated: 2021/05/06 13:49:39 by jiholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		get_time(void)
{
	struct timeval mytime;

	gettimeofday(&mytime, NULL);
	return (mytime.tv_sec * 1000 + mytime.tv_usec / 1000);
}

int		parse(char *argv[])
{
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 ||
		ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0 ||
		(argv[5] && ft_atoi(argv[5]) <= 0))
		return (1);
	table()->num_philo = ft_atoi(argv[1]);
	table()->time_to_die = ft_atoi(argv[2]);
	table()->time_to_eat = ft_atoi(argv[3]);
	table()->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table()->must_eat = ft_atoi(argv[5]);
	else
		table()->must_eat = -1;
	table()->base_time = get_time();
	return (0);
}

void	init_sema(void)
{
	sem_unlink("fork");
	sem_unlink("msg");
	table()->fork = sem_open("fork", O_CREAT, 0644, table()->num_philo);
	table()->m_msg = sem_open("msg", O_CREAT, 0644, 1);
}

int		main(int argc, char *argv[])
{
	if (!(argc == 5 || argc == 6) || parse(argv))
		return (printf("input Error\n"));
	init_sema();
	create_philo();

	printf("end\n");
	return (0);
}

void	create_philo(void)
{
	int			i;
	i = -1;

	t_philos	*philo;

	if (!(philo = malloc(sizeof(t_philos) * table()->num_philo)))
		return ;
	while (++i < table()->num_philo)
	{
        philo[i].nbr = i + 1;
        philo[i].eat = 0;
        philo[i].last_eat = get_time();
        philo[i].pid = fork();
        if (philo[i].pid == 0)
        {   
            run(&philo[i]);
        }
    }
    monitor(philo);
	// check_dead();
}

void	pkill(t_philos *phi)
{
	int i;

	i = -1;
	while (++i < table()->num_philo)
		kill(phi[i].pid, SIGKILL);
	return ;
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
		printf("main : %d\n", WEXITSTATUS(status));
		if (WEXITSTATUS(status) == 0)
		{
			eat++;
			if (eat == table()->num_philo)
				return ;
		}
		else if (WEXITSTATUS(status) == 1)
		{
			pkill(phi);
			return ;
		}
	}
}

