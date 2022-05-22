/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:01:17 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/22 14:32:17 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*loop_thread(void *p)
{
	t_man	*man;

	man = p;
	while (*(man->sim_done) == false)
	{
		// printf("22 %d %lld %d\n", man->time_to_die, man->last_eat_time, man->id);
		phil_eat(man);
		phil_sleep(man);
		phil_think(man);
	}
	return (NULL);
}

void	launcher(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_of_phils)
		pthread_create(&info->men[i].thread, NULL, &loop_thread, (void *)&info->men[i]);
	i = -1;
	while (++i < info->num_of_phils)
		pthread_join(info->men[i].thread, NULL);
}
