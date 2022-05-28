/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 23:01:59 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/28 23:10:06 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_all_mutexes(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_of_phils)
		pthread_mutex_destroy(&(info->forks[i]));
	pthread_mutex_destroy(&(info->sim_done_mutex));
	pthread_mutex_destroy(&(info->done_phils_mutex));
	pthread_mutex_destroy(&(info->time_keeper_mutex));
}

int	deinit_info(t_info *info)
{
	destroy_all_mutexes(info);
	free_all(info);
	return (0);
}
