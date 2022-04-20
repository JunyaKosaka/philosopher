/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:08:34 by jkosaka           #+#    #+#             */
/*   Updated: 2022/04/19 18:14:30 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat] */ 
static int	init_philo(t_info *info, int argc, char **argv)
{
	info->num_of_phils = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->must_eat_cnt = ft_atoi(argv[5]);
	// intにならない時のエラーチェック
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
	// man.num_of_phils = info->num_of_phils; // この初期化必要か考える
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
	struct timeval	tv;
	int				id;

	id = 1;
	gettimeofday(&tv, NULL);
	print_log(tv.tv_sec, tv.tv_usec, id, FORK_MSG);
	print_log(tv.tv_sec, tv.tv_usec + time_to_die, id, DIED_MSG);
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
		printf("%d %d\n", i, prev);
	}
	return (0);
}

int	philosopher(int argc, char **argv)
{
	t_info	info;

	info = (t_info){0}; // 複合リテラル
	printf("%d\n", info.num_of_phils);
	if (init_philo(&info, argc, argv))
		return (error_handler(USAGE_MSG));
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
