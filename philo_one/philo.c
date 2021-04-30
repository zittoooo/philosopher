#include "philo_one.h"

void	msg(t_philos *philo, int status, unsigned long timestamp)
{
	pthread_mutex_lock(&table()->m_msg);
	if (table()->dead)
	{
		pthread_mutex_unlock(&table()->m_msg);
		return ;
	}
	if (status == EAT)
		printf("%ld %d is eating\n", timestamp, philo->nbr);
	else if (status == TAKEN)
		printf("%ld %d has taken a fork\n", timestamp, philo->nbr);
	else if (status == SLEEP)
		printf("%ld %d is sleeping\n", timestamp, philo->nbr);
	else if (status == THINK)
		printf("%ld %d is thinking\n", timestamp, philo->nbr);
	else if (status == DEAD)
	{
		printf("%ld %d died\n", timestamp, philo->nbr);
		table()->dead = 1;
	}
	pthread_mutex_unlock(&table()->m_msg);
}

int		eat(t_philos *philo)
{
	pthread_mutex_lock(&table()->fork[philo->fork1]);
	if (table()->dead == 1)
		return (END);
	msg(philo, TAKEN, get_time() - table()->base_time);
	pthread_mutex_lock(&table()->fork[philo->fork2]);
	if (table()->dead == 1)
		return (END);
	msg(philo, TAKEN, get_time() - table()->base_time);
	msg(philo, EAT, get_time() - table()->base_time);
	philo->last_eat = get_time();
	usleep(table()->time_to_eat * 1000);
	pthread_mutex_unlock(&table()->fork[philo->fork1]);
	pthread_mutex_unlock(&table()->fork[philo->fork2]);
	philo->eat++;
	if (philo->eat == table()->must_eat)
	{
		table()->eat++;
		return (END);  // 먹어야 하는 만큼 먹었으면 스레드 끝내기
	}
	return (ALIVE);
}

int		sleep_philo(t_philos *philo)
{
	int cur;

	if (table()->dead)
		return (END);
	msg(philo, SLEEP, get_time() - table()->base_time);
	cur = get_time();
	while (get_time() - cur <= table()->time_to_sleep && !table()->dead)
		usleep(1);
	return (ALIVE);
}

int		think(t_philos *philo)
{
	if (table()->dead)
		return (END);
	msg(philo, THINK, get_time() - table()->base_time);
	return (ALIVE);
}
