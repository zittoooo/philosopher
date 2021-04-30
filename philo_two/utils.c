#include "philo_two.h"

t_philo		*philo(void)
{
	static	t_philo philo;

	return (&philo);
}

t_table		*table(void)
{
	static	t_table table;

	return (&table);
}

int			ft_atoi(char *str)
{
	int ret;
	int sign;
	int i;

	i = 0;
	sign = 1;
	ret = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	return (ret * sign);
}