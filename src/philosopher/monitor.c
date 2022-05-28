/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 20:18:08 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/28 22:00:46 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  done simulation  */
static bool	done_sim(t_info *info)
{
	bool	done;

	pthread_mutex_lock(&info->sim_done_mutex);
	done = info->sim_done;
	pthread_mutex_unlock(&info->sim_done_mutex);
	return (done);
}

/*  monitor all philosophers  */
static void	monitor_phils(t_info *info, int time_to_die, long long cur_time)
{
	long long	last_eat_time;
	int			i;

	pthread_mutex_lock(&(info->time_keeper_mutex));
	i = -1;
	while (++i < info->num_of_phils)
	{
		last_eat_time = info->men[i].last_eat_time;
		if (time_to_die <= cur_time - last_eat_time)
			print_log(&info->men[i], DIED_MSG);
	}
	pthread_mutex_unlock(&(info->time_keeper_mutex));
}

void	*monitor_thread(void *p)
{
	t_info		*info;
	long long	cur_time;
	int			time_to_die;

	info = p;
	pthread_mutex_lock(&info->time_keeper_mutex);
	time_to_die = info->time_to_die;
	pthread_mutex_unlock(&info->time_keeper_mutex);
	while (done_sim(info) == false)
	{
		usleep(500);
		cur_time = get_millisec();
		monitor_phils(info, time_to_die, cur_time);
	}
	return (NULL);
}
