#include "philo_one.h"

void	*watch(void	*phi)
{
	long cur;
	t_philos *philo;

	philo = (t_philos *)phi;
	while (!table()->dead)
	{
		if (table()->eat == table()->must_eat)
			break ;
		cur = get_time();
		if ((cur - philo->last_eat) > table()->time_to_die)
		{
			// printf("%lu %ld\n", cur,  philo->last_eat);
			// printf("id : %d  %lu\n", philo->nbr, (cur - philo->last_eat));
			msg(phi, DEAD, get_time() - table()->base_time);
			table()->dead = 1;
			break ;
		}
	}
	return (NULL);
}

void	*run(void *phi)
{
	pthread_t monitor;
	t_philos *philo;

	philo = (t_philos *)phi;
	if (philo->nbr % 2)
		usleep(80);
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

void    create_philo()
{
	int i;

	i = 0;
	t_philos *philo;
	if (!(philo = malloc(sizeof(t_philos) * table()->num_philo)))
	 return ;
	while (i < table()->num_philo)
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
		i++;
	}
	i = -1;
	while (++i < table()->num_philo)
		pthread_join(philo[i].tid, NULL);
}