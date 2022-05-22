/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:02:31 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/22 16:10:30 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

/*  error message */
# define USAGE_MSG 	"[usage]: ./philo <philos> <die> <eat> <sleep> (<must>)"
# define MUTEX_ERR_MSG "pthread_mutex_init error"
# define MALLOC_ERR_MSG "malloc error"

# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DIED_MSG "died"

// typedef struct timeeval t_timeeval;

typedef struct s_man
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*baton;  // logを書く時など自分にbatonが必要
	pthread_mutex_t	*done_persons;
	pthread_t		thread;
	long long		last_eat_time;
	int				num_of_phils;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_cnt;
	
	int				my_eat_cnt;
	int				id;
	int				*done_persons_cnt;
	bool			*sim_done; // 終わったかどうか
}	t_man;

typedef struct s_info
{
	t_man			*men; // 人数分の配列
	pthread_mutex_t	*forks;
	pthread_mutex_t	baton;
	pthread_mutex_t	done_persons;
	int				num_of_phils;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				done_persons_cnt;
	int				must_eat_cnt;
	bool			sim_done;
}	t_info;

/*  philo  */
int		philosopher(int argc, char **argv);
void	print_log(t_man *man, char *msg);
void	launcher(t_info *info);
int		solo_philo(int time_to_die);

/*  fork  */
void	take_two_forks(t_man *man);
void	unlock_two_forks(t_man *man);

/*  action  */
void	phil_wait(t_man *man, int waiting_time);
void	phil_eat(t_man *man);
void	phil_sleep(t_man *man);
void	phil_think(t_man *man);

/*  utils  */
int		error_handler(char *msg);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);

int		free_all(t_info *info);
long long	get_millisec(void);

#endif // PHILO_H
