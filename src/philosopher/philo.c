/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:08:34 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/25 19:38:43 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  initialize all philosophers  */
static int	init_men(t_info *info)
{
	t_man	man;
	int		i;

	info->men = (t_man *)malloc(sizeof(t_man) * info->num_of_phils);
	if (!(info->men))
		return (error_handler(MALLOC_ERR_MSG));
	man = (t_man){0};
	man.sim_done_mutex = &(info->sim_done_mutex);
	man.done_phils_mutex = &(info->done_phils_mutex);
	man.time_keeper_mutex = &(info->time_keeper_mutex);
	man.last_eat_time = get_millisec();
	man.num_of_phils = info->num_of_phils;
	man.time_to_die = info->time_to_die;
	man.time_to_eat = info->time_to_eat;
	man.time_to_sleep = info->time_to_sleep;
	man.must_eat_cnt = info->must_eat_cnt;
	man.done_phils_cnt = &(info->done_phils_cnt);
	man.sim_done = &(info->sim_done);
	i = -1;
	while (++i < info->num_of_phils)
	{
		man.id = i + 1;
		info->men[i] = man;
	}
	return (0);
}

/*  initialize all forks  */
static int	init_forks(t_info *info)
{
	int	i;
	int	prev;

	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
							info->num_of_phils);
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
	}
	return (0);
}

static void	destroy_all_mutexes(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_of_phils)
		pthread_mutex_destroy(&(info->forks[i]));
	pthread_mutex_destroy(&(info->sim_done_mutex));
	pthread_mutex_destroy(&(info->done_phils_mutex));
	pthread_mutex_destroy(&(info->time_keeper_mutex));
}

static int	init_info(t_info *info)
{
	if (pthread_mutex_init(&(info->sim_done_mutex), NULL))
		return (error_handler(MUTEX_ERR_MSG));
	if (pthread_mutex_init(&(info->done_phils_mutex), NULL))
		return (error_handler(MUTEX_ERR_MSG));
	if (pthread_mutex_init(&(info->time_keeper_mutex), NULL))
		return (error_handler(MUTEX_ERR_MSG));
	if (init_men(info))
		return (1);
	if (init_forks(info))
		return (1);
	return (0);
}

int	philosopher(t_info *info)
{
	if (info->num_of_phils == 1)
		return (solo_philo(info->time_to_die));
	if (init_info(info))
		return (free_all(info));
	launcher(info);
	destroy_all_mutexes(info);
	return (free_all(info));
}
