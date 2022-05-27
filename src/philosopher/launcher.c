/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:01:17 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/27 12:28:31 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	count_done_phils(t_man *man)
{
	int	cnt;

	pthread_mutex_lock(man->done_phils_mutex);
	cnt = *(man->done_phils_cnt);
	pthread_mutex_unlock(man->done_phils_mutex);
	return (cnt);
}

/*  check if eat count reached must_eat_cnt  */
static void	check_eat_cnt(t_man *man)
{
	if (man->my_eat_cnt != man->must_eat_cnt)
		return ;
	pthread_mutex_lock(man->done_phils_mutex);
	*(man->done_phils_cnt) += 1;
	pthread_mutex_unlock(man->done_phils_mutex);
	if (count_done_phils(man) == man->num_of_phils)
	{
		pthread_mutex_lock(man->sim_done_mutex);
		*(man->sim_done) = true;
		pthread_mutex_unlock(man->sim_done_mutex);
	}
}

/*  a philosopher whose id is even wait at the beginning  */
static void	start_alternately(t_man *man)
{
	if ((man->id & 1) == 0)
		phil_wait(man, ft_max(1, man->time_to_eat / 2));
	else if (man->num_of_phils & 1 && man->id == man->num_of_phils)
		phil_wait(man, ft_max(2, man->time_to_eat / 2 * 3));
}

void	*loop_thread(void *p)
{
	t_man	*man;

	man = p;
	start_alternately(man);
	while (!done_simulation(man))
	{
		phil_eat(man);
		check_eat_cnt(man);
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
		pthread_create(&info->men[i].thread, NULL, &loop_thread, \
						(void *)&info->men[i]);
	pthread_create(&info->monitor, NULL, &monitor_thread, info);
	pthread_join(info->monitor, NULL);
	i = -1;
	while (++i < info->num_of_phils)
		pthread_join(info->men[i].thread, NULL);
}
