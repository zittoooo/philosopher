#include "philo_three.h"

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
	printf("id : %d\n", philo->nbr);
	return (NULL);
}

void	run(t_philos *philo)
{
	pthread_t	monitor;

	// printf("%d\n", philo->nbr);
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