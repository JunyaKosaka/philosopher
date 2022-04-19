/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:02:31 by jkosaka           #+#    #+#             */
/*   Updated: 2022/04/18 23:39:17 by jkosaka          ###   ########.fr       */
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

# define USAGE_MSG 	"[usage]: ./philo <philos> <die> <eat> <sleep> (<must>)"
# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DIED_MSG "is died"	
	

typedef struct s_man
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	long long		last_eat;
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
	t_man	*men; // 人数分の配列
	int		num_of_phils;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat_cnt;
}	t_info;

/*  philo  */
int		philosopher(int argc, char **argv);
void	print_log(long sec, int usec, int id, char *msg);


/*  utils  */
int		error_handler(char *msg);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);

#endif // PHILO_H
