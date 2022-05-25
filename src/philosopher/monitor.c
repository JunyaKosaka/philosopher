/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 20:18:08 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/25 17:51:40 by jkosaka          ###   ########.fr       */
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
	int			i;

	info = p;
	while (done_sim(info) == false)
	{
		cur_time = get_millisec();
		i = -1;
		while (++i < info->num_of_phils)
		{
			if (info->time_to_die < cur_time - info->men[i].last_eat_time)
				print_log(&(info->men[i]), DIED_MSG);
		}
		usleep(500);
	}
	return (NULL);
}
