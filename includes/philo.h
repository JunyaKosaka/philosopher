/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:02:31 by jkosaka           #+#    #+#             */
/*   Updated: 2022/04/19 18:07:50 by jkosaka          ###   ########.fr       */
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
# define DIED_MSG "is died"

// typedef struct timeeval t_timeeval;

typedef struct s_man
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	long long		last_eat_time;
	int				num_of_phils;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	
	int				total_eat_cnt;
	int				my_eat_cnt;
	int				*total_ate_cnt;
	int				id;
	bool			*done;
}	t_man;

typedef struct s_info
{
	t_man			*men; // 人数分の配列
	pthread_mutex_t	*forks;
	int				num_of_phils;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_cnt;
}	t_info;

/*  philo  */
int		philosopher(int argc, char **argv);
void	print_log(long sec, int usec, int id, char *msg);
void	launcher(t_info *info);

/*  utils  */
int		error_handler(char *msg);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);

#endif // PHILO_H
