/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:01:17 by jkosaka           #+#    #+#             */
/*   Updated: 2022/04/19 20:16:07 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  philosopher takes the first fork  */
void	first_fork(t_man *man)
{
	struct timeval	tv;

	if (man->id & 1)
	{
		pthread_mutex_lock(man->left_fork);	
	}
	else
	{
		usleep(100);
		pthread_mutex_lock(man->right_fork);	
	}
	gettimeofday(&tv, NULL);
	print_log(tv.tv_sec, tv.tv_usec, man->id, FORK_MSG);
}

/*  philosopher takes the second fork  */
void	second_fork(t_man *man)
{
	struct timeval	tv;

	if (man->id & 1)
	{
		pthread_mutex_lock(man->right_fork);	
	}
	else
	{
		pthread_mutex_lock(man->left_fork);	
	}
	gettimeofday(&tv, NULL);
	print_log(tv.tv_sec, tv.tv_usec, man->id, FORK_MSG);
}

void	unlock_fork(t_man *man)
{
	pthread_mutex_unlock(man->left_fork);
	pthread_mutex_unlock(man->right_fork);
}

void	eat(t_man *man)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	print_log(tv.tv_sec, tv.tv_usec, man->id, EAT_MSG);
}

void	*loop_thread(void *p)
{
	t_man	*man;
	int		cnt;

	man = p;
	printf("70:%d\n", man->id);
	cnt = 0;
	while (1)
	{
		first_fork(man);
		second_fork(man);
		eat(man);
		unlock_fork(man);
		usleep(man->time_to_eat);
		
		usleep(man->time_to_sleep);
		cnt++;
		if (cnt >= 10) break ;
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
