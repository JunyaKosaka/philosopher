/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:50:21 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/26 12:55:29 by jkosaka          ###   ########.fr       */
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

/*  solo philosopher cannot survive  */
int	solo_philo(int time_to_die)
{
	long long	time;
	int			id;

	time = get_millisec();
	id = 1;
	printf("%lld %d %s\n", time, id, FORK_MSG);
	solo_wait(time_to_die);
	time = get_millisec();
	printf("%lld %d %s\n", time, id, DIED_MSG);
	return (0);
}
