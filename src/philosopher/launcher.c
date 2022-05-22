/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:01:17 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/22 13:40:24 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*loop_thread(void *p)
{
	t_man	*man;
	int		cnt;

	man = p;
	cnt = 0;
	while (*(man->sim_done) == false) // 
	{
		phil_eat(man);
		phil_sleep(man);
		phil_think(man);
		cnt++;
		// if (cnt >= 2) break ;
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
