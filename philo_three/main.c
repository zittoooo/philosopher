#include "philo_three.h"

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
	table()->eat = 0;
	table()->dead = 0;
	return (0);
}

int		main(int argc, char *argv[])
{
	if (!(argc == 5 || argc == 6) || parse(argv))
		return (printf("input Error\n"));
	
}

void	create_philo(void)
{
	int			i;
    pid_t       pid;
	i = -1;

	t_philos	*philo;

	if (!(philo = malloc(sizeof(t_philos) * table()->num_philo)))
		return ;
	while (++i < table()->num_philo)
	{
        philo[i].nbr = i + 1;
        philo[i].eat = 0;
        philo[i].last_eat = get_time();
        philo[i].pid = pid;
        pid = fork();
        if (pid == 0)
        {   
            while (1)
            {   
                run(&philo[i]);
            }
        }
    }
    if (pid != 0)
    {
        //wait()
    }

        
	check_dead();
}

