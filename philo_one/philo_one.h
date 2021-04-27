#ifndef PHILO_ONE
# define PHILO_ONE

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>

# define EAT 1
# define TAKEN 2
# define SLEEP 3
# define THINK 4
# define DEAD 5

typedef struct      s_table
{
	// 인자로 들어오는 순서대로
	int				num_philo;  // 철학자 수 = 포크 수
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				must_eat;

	unsigned long	base_time;	// 기준 시간 /* ms 로 바꾸는 시간 단위는 unsigned long 으로 */
	int				eat;		// 다 먹은 철학자 수
	int				dead;		// 철학자가 한명이라도 죽으면 1
	pthread_mutex_t	*fork;		// 철학자의 수만큼 만들 포크 뮤텍스
	pthread_mutex_t	m_msg;		// 메세지가 꼬이지 않아야 해서 필요한 뮤텍스
}					t_table;

typedef struct		s_philo
{
	int				nbr;		//철학자 번호
	int				fork1;
	int				fork2;
	int				eat;		// 철학자가 먹은 횟수
	long	last_eat;	// 철학자가 마지막으로 밥 먹은 시간  /* ms 로 바꾸는 시간 단위는 unsigned long 으로 */
	pthread_t		tid;		// 철학자 쓰레드 아이디
}					t_philos;

t_philos     	*philos();
t_table			*table();
int			ft_atoi(char *str);


unsigned long	get_time();


void    create_philo();
void	*run(void *phi);
void	*watch(void	*phi);

void	msg(t_philos *philo, int status, unsigned long timestamp);
int		eat(t_philos *philo);
int		sleep_philo(t_philos *philo);
void	philo_usleep(t_philos *philo, unsigned long sleep);
int		think(t_philos *philo);

#endif