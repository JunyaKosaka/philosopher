/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:50:21 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/25 17:50:40 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  solo philosopher cannot survive  */
int	solo_philo(int time_to_die)
{
	long long	time;
	int			id;

	time = get_millisec();
	id = 1;
	printf("%lld %d %s\n", time, id, FORK_MSG);
	usleep(time_to_die * 1000);
	printf("%lld %d %s\n", time + time_to_die, id, DIED_MSG);
	return (0);
}
