#include "philo_one.h"

t_philos     *philos()
{
	static	t_philos philo;

	return (&philo);
}

t_table		*table()
{
	static	t_table	table;

	return (&table);
}

int			ft_atoi(char *str)
{
	int ret;
	int sign;
	int i;

	i = 0;
	ret = 0;
	sign = 1;

	if (str[i] == '-' && i++)
		sign = -1;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	return (ret * sign);
}