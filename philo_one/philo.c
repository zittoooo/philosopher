#include "philo_one.h"

void	*run(void	*arg)
{
	// pthread_t monitor;

	// pthread_create(&monitor, NULL, watch, NULL);
	while (1)
	{
		if (eat())
			break ;
		else if (sleep())
			break ;
		else if (think())
			break ;
		
	}

	// pthread_join(&monitor, NULL);
}

void    create_philo()
{
	int i;

	i = 0;
	t_philos *philo;

	philo = malloc(sizeof(t_philos) * table()->num_philo);
	while (i < table()->num_philo)
	{
		philo[i].nbr = i + 1;
//		philo[i].fork1 = ;
//		philo[i].fork2 = ;
		philo[i].eat = 0;
		philo[i].last_eat = start_time();
		pthread_creat(&philo[i].tid, NULL, run, NULL);
		i++;
	}
	// i = 0;
	// while (i < table()->num_philo)
	// {
	// 	pthread_join(&philo[i].tid, NULL);	
	// 	i++;
	// }
}