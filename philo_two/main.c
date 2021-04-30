#include "philo_two.h"

int		parse(char **argv)
{
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) ||
		ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0 || 
		(argv[5] && ft_atoi(argv[5]) <= 0))
		return (1);
}

int		main(int argc, char	*argv[])
{
	if (!(argc == 5 || argc == 6) || parse(argv))
		return (printf("input error"));

}