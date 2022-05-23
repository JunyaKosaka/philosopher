/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 23:33:44 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/23 12:49:44 by jkosaka          ###   ########.fr       */
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
		{
			*(man->sim_done) = true;
		}
	}
	// if (*(man->sim_done) == true)
	// 	printf("32 %d\n", man->id);
	pthread_mutex_unlock(man->baton);
	// if (*(man->sim_done) == true)
	// 	printf("33 %d\n", man->id);
}
