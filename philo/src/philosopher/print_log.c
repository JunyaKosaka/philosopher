/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 23:33:44 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/30 23:19:42 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	done_simulation(t_man *man)
{
	bool	done;

	pthread_mutex_lock(man->sim_done_mutex);
	done = *(man->sim_done);
	pthread_mutex_unlock(man->sim_done_mutex);
	return (done);
}

/*  print log with message  */
void	print_log(t_man *man, char *msg)
{
	long long	time;

	if (done_simulation(man))
		return ;
	pthread_mutex_lock(man->sim_done_mutex);
	if (*(man->sim_done) == false)
	{
		time = get_millisec();
		printf("%lld %d %s\n", time, man->id, msg);
		if (!ft_strcmp(msg, DIED_MSG))
			*(man->sim_done) = true;
	}
	pthread_mutex_unlock(man->sim_done_mutex);
}
