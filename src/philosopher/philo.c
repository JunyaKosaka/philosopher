/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:08:34 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/22 12:40:53 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat] */ 
static int	init_info(t_info *info, int argc, char **argv)
{
	info->num_of_phils = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->done_persons_cnt = 0;
	info->must_eat_cnt = -1;
	info->sim_done = false; // 複合リテラルがあるので不要のはず
	if (argc == 6)
	{
		info->must_eat_cnt = ft_atoi(argv[5]); // ここで0の時は終了すべき
		printf("27 %d\n", info->must_eat_cnt);
	}
	// intにならない時のエラーチェック
	pthread_mutex_init(&(info->baton), NULL);
	pthread_mutex_init(&(info->done_persons), NULL);
	return (0);
}

static int	init_men(t_info *info)
{
	t_man	man;
	int		i;

	info->men = (t_man *)malloc(sizeof(t_man) * info->num_of_phils);
	if (!(info->men))
		return (error_handler("malloc error"));
	man = (t_man){0};
	man.baton = &(info->baton);
	man.done_persons = &(info->done_persons);
	man.last_eat_time = get_millisec();
	man.num_of_phils = info->num_of_phils; // この初期化必要か考える
	man.time_to_die = info->time_to_die;
	man.time_to_eat = info->time_to_eat;
	man.time_to_sleep = info->time_to_sleep;
	man.must_eat_cnt = info->must_eat_cnt;
	man.my_eat_cnt = 0;  // 不要
	man.done_persons_cnt = &(info->done_persons_cnt);
	man.sim_done = &(info->sim_done);
	i = -1;
	while (++i < info->num_of_phils)
	{
		man.id = i + 1;
		info->men[i] = man;
	}
	return (0);
}

static int	solo_philo(int time_to_die)
{
	long long	time;
	int		id;

	time = get_millisec();
	id = 1;
	printf("%lld %d %s\n", time, id, FORK_MSG);
	usleep(time_to_die);
	printf("%lld %d %s\n", time + time_to_die, id, FORK_MSG);
	return (1);
}

static int	init_forks(t_info *info)
{
	int	i;
	int	prev;

	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->num_of_phils);
	if (!info->forks)
		return (error_handler(MALLOC_ERR_MSG));
	i = -1;
	while (++i < info->num_of_phils)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
			return (error_handler(MUTEX_ERR_MSG));
	}
	i = -1;
	while (++i < info->num_of_phils)
	{
		prev = (i - 1 + info->num_of_phils) % info->num_of_phils;
		info->men[i].left_fork = &info->forks[i];
		info->men[i].right_fork = &info->forks[prev];
		// printf("%d %d\n", i, prev);
	}
	return (0);
}

int	philosopher(int argc, char **argv)
{
	t_info	info;

	info = (t_info){0}; // 複合リテラル
	if (init_info(&info, argc, argv))
		return (error_handler(USAGE_MSG));
	printf("num of phils:%d\n", info.num_of_phils);
	if (info.num_of_phils == 1)
		return (solo_philo(info.time_to_die));
	if (init_men(&info)) // ここでmenをmalloc
		return (1); // free_all(&info);
	if (init_forks(&info))
		return (1); // free_all(&info);
	// if (init_eat(&info))
	// 	return (1); // free_all(&info);
	launcher(&info);
	printf("%d\n", info.time_to_eat);
	return (0);	
}
