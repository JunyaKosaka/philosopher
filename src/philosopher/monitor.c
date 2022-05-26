/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 20:18:08 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/26 17:27:24 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	done_sim(t_info *info)
{
	bool	done;

	pthread_mutex_lock(&info->sim_done_mutex);
	done = info->sim_done;
	pthread_mutex_unlock(&info->sim_done_mutex);
	return (done);
}

void	*monitor_thread(void *p)
{
	t_info		*info;
	long long	cur_time;
	long long	last_eat_time;
	int			time_to_die;
	int			i;

	info = p;
	pthread_mutex_lock(&info->time_keeper_mutex);
	time_to_die = info->time_to_die;
	pthread_mutex_unlock(&info->time_keeper_mutex);
	usleep(1000);
	while (done_sim(info) == false)
	{
		usleep(500);
		cur_time = get_millisec();
		i = -1;
		while (++i < info->num_of_phils)
		{
			pthread_mutex_lock(info->men[i].time_keeper_mutex);
			last_eat_time = info->men[i].last_eat_time;
			if (time_to_die < cur_time - last_eat_time)
				print_log(&info->men[i], DIED_MSG);
			pthread_mutex_unlock(info->men[i].time_keeper_mutex);
		}
	}
	return (NULL);
}
