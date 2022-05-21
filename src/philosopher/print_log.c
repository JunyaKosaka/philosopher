/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 23:33:44 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/21 18:23:32 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  print log with message  */
void	print_log(t_man *man, char *msg)
{
	long long	time;

	pthread_mutex_lock(man->baton);
	if (*(man->sim_done) == false)
	{
		time = get_millisec();
		printf("%lld %d %s\n", time, man->id, msg);
	}
	pthread_mutex_unlock(man->baton);
}
