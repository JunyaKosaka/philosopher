/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 23:33:44 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/24 20:11:53 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  print log with message  */
void	print_log(t_man *man, char *msg)
{
	long long	time;

	if (done_simulation(man))
		return ;
	if (!done_simulation(man))
	{
		time = get_millisec();
		printf("%lld %d %s\n", time, man->id, msg);
		if (!ft_strcmp(msg, DIED_MSG))
		{
			pthread_mutex_lock(man->baton);
			*(man->sim_done) = true;
			pthread_mutex_unlock(man->baton);
		}
	}
}
