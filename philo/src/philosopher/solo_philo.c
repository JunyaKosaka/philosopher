/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:50:21 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/30 23:41:25 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	solo_wait(int waiting_time)
{
	long long	start;
	long long	cur_time;

	start = get_millisec();
	cur_time = start;
	while (cur_time - start < waiting_time)
	{
		usleep(500);
		cur_time = get_millisec();
	}
}

void	*solo_loop_thread(void *p)
{
	t_man		*man;

	man = p;
	pthread_mutex_lock(man->left_fork);
	print_log(man, FORK_MSG);
	pthread_mutex_unlock(man->left_fork);
	solo_wait(man->time_to_die);
	print_log(man, DIED_MSG);
	return (NULL);
}

int	solo_philo(t_info *info)
{
	pthread_create(&info->men[0].thread, NULL, &solo_loop_thread, \
			(void *)&info->men[0]);
	pthread_join(info->men[0].thread, NULL);
	deinit_info(info);
	return (0);
}
