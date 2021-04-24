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