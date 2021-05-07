/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiholee <jiholee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 15:46:08 by jiholee           #+#    #+#             */
/*   Updated: 2021/05/07 16:23:12 by jiholee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <semaphore.h>

# define EAT 1
# define TAKEN 2
# define SLEEP 3
# define THINK 4
# define DEAD 5

# define END 1
# define ALIVE 0

typedef struct		s_table
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				base_time;
	int				eat;
	int				dead;
	sem_t			*fork;
	sem_t			*m_msg;
}					t_table;

typedef struct		s_philo
{
	int				nbr;
	int				eat;
	int				last_eat;
	pthread_t		tid;
}					t_philos;

/*
** main.c
*/
int					get_time();
void				clean(void);

/*
** create_philo.c
*/
void				create_philo(void);
void				*run(void *phi);
void				*watch(void	*phi);
void				check_dead(void);
/*
** utils.c
*/
t_philos			*philos();
t_table				*table();
int					ft_atoi(char *str);
void				philo_eat_msg(t_philos *philo, unsigned long timestamp);

/*
** philo.c
*/
void				msg(t_philos *philo, int status, unsigned long timestamp);
int					eat(t_philos *philo);
int					sleep_philo(t_philos *philo);
int					think(t_philos *philo);
void				post_sem(void);
#endif
