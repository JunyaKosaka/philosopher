/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 20:18:08 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/25 19:38:43 by jkosaka          ###   ########.fr       */
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
	t_man		man;
	long long	cur_time;
	long long	last_eat_time;
	int			i;

	info = p;
	while (done_sim(info) == false)
	{
		cur_time = get_millisec();
		i = -1;
		while (++i < info->num_of_phils)
		{
			man = info->men[i];
			pthread_mutex_lock(man.time_keeper_mutex);
			last_eat_time = man.last_eat_time;
			pthread_mutex_unlock(man.time_keeper_mutex);
			if (info->time_to_die < cur_time - last_eat_time)
				print_log(&man, DIED_MSG);
		}
		usleep(500);
	}
	return (NULL);
}
