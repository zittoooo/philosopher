#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <stdio.h>

# define TAKEN 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DEAD 4

typedef struct	s_table
{
	int			num_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat;

	int			base_time;
	int			eat; // 다 먹은 철학자 수
	int			dead; // 철학자가 한명이라도 죽으면 1
	sem_t		*eat;
	sem_t		*msg;
}				t_table;

typedef	struct s_philo
{
	int			nbr;
	int			eat; // 철학자가 먹은 횟수
	int			last_eat; // 철학자가 마지막으로 밥 먹은 시간
	pthread_t	tid;
}				t_philo;

#endif