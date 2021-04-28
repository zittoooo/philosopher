#include "philo_one.h"

void	msg(t_philos *philo, int status, unsigned long timestamp)
{
	pthread_mutex_lock(&table()->m_msg);
	if (table()->dead)
	{
		pthread_mutex_unlock(&table()->m_msg);
		return ;
	}
	else if (status == EAT)
	{
		printf("%ld %d is eating\n", timestamp, philo->nbr);
	}
	else if (status == TAKEN)
	{
		printf("%ld %d has taken a fork\n", timestamp, philo->nbr);
	}
	else if (status == SLEEP)
	{
		printf("%ld %d is sleeping\n", timestamp, philo->nbr);
	}
	else if (status == THINK)
	{
		printf("%ld %d is thinking\n", timestamp, philo->nbr);
	}
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
	msg(philo, TAKEN, get_time() - table()->base_time);
	pthread_mutex_lock(&table()->fork[philo->fork2]);
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
		return (1);  // 먹어야 하는 만큼 먹었으면 스레드 끝내기
	}
	return (0);
}

int		sleep_philo(t_philos *philo)
{
	msg(philo, SLEEP, get_time() - table()->base_time);
	// philo_usleep(philo, table()->time_to_sleep);
	usleep(table()->time_to_sleep * 1000);
	return (0);
}

// void	philo_usleep(t_philos *philo, unsigned long sleep)
// {
// 	unsigned long cur;

// 	cur = get_time();
// 	while (get_time() - cur <= sleep && !table()->dead)
// 		usleep(1);
// }

int		think(t_philos *philo)
{
	msg(philo, THINK, get_time() - table()->base_time);
	return (0);
}
