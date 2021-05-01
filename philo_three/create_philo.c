#include "philo_three.h"

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
	printf("id : %d\n", philo->nbr);
	return (NULL);
}

void	run(t_philos *philo)
{
	pthread_t	monitor;

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