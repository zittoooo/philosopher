#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>

# define EAT 1
# define TAKEN 2
# define SLEEP 3
# define THINK 4
# define DEAD 5

# define END 1
# define ALIVE 0

typedef struct		s_table
{
	int				num_philo;  // 철학자 수 = 포크 수
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;

	int				base_time;	// 기준 시간
	sem_t	*fork;		// 철학자의 수만큼 만들 포크 뮤텍스
	sem_t	*m_msg;		// 메세지가 꼬이지 않아야 해서 필요한 뮤텍스
}					t_table;

typedef struct		s_philo
{
	int				nbr;		//철학자 번호
	int				eat;		// 철학자가 먹은 횟수
	int				last_eat;	// 철학자가 마지막으로 밥 먹은 시간  
	pid_t			pid;		// 철학자 쓰레드 아이디
}					t_philos;   // sizeof == 32

/*
** main.c
*/
int					get_time();
void				clean(void);
void				monitor(t_philos *phi);
/*
** create_philo.c
*/
void				create_philo(void);
void				run(t_philos *philo);
void				*watch(void	*phi);
void 				check_dead(void);
/*
** utils.c
*/
t_philos			*philos();
t_table				*table();
int					ft_atoi(char *str);

/*
** philo.c
*/
void				msg(t_philos *philo, int status, unsigned long timestamp);
int					eat(t_philos *philo);
int					sleep_philo(t_philos *philo);
int					think(t_philos *philo);

#endif
