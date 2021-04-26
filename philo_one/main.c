#include "philo_one.h"


unsigned long	start_time()
{
	struct timeval mytime;

	gettimeofday(&mytime, NULL);
	return (mytime.tv_sec * 1000 + mytime.tv_usec/1000);
}

int		parse(char	*argv[])
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
	table()->base_time = start_time();
	table()->eat = 0;
	table()->dead = 0;
	return (0);
}

void	init_mutex()
{
	int i;

	i = 0;
	table()->fork = malloc(sizeof(pthread_mutex_t) * table()->num_philo);
	while (i < table()->num_philo)
	{
		pthread_mutex_init(&table()->fork[i], NULL);
		i++;
	}
}

int		main(int argc, char *argv[])
{
	if (!(argc == 5 || argc == 6) || parse(argv))
		return (printf("input Error"));
	init_mutex();
	create_philo();
}