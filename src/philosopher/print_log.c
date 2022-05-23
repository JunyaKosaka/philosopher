/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 23:33:44 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/23 15:22:22 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  print log with message  */
void	print_log(t_man *man, char *msg)
{
	long long	time;

	if (*(man->sim_done) == true)
		return ;
	pthread_mutex_lock(man->baton);
	if (*(man->sim_done) == false)
	{
		time = get_millisec();
		printf("%lld %d %s\n", time, man->id, msg);
		if (!ft_strcmp(msg, DIED_MSG))
			*(man->sim_done) = true;
	}
	pthread_mutex_unlock(man->baton);
}
