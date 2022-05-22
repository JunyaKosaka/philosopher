/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 13:36:54 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/22 13:40:08 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  wait until waiting_time passes  */
void	phil_wait(t_man *man, int waiting_time)
{
	long long	start;
	long long	cur_time;

	start = get_millisec();
	cur_time = start;
	while (cur_time - start < waiting_time)
	{
		cur_time = get_millisec();
		if (man->time_to_die <= cur_time - man->last_eat_time)
		{
			print_log(man, DIED_MSG);
			*(man->sim_done) = true;
			return ;
		}
		usleep(50);
	}
}

/*  check if eat count reached must_eat_cnt  */
static void	check_eat_cnt(t_man *man)
{
	if (man->my_eat_cnt == man->must_eat_cnt)
	{
		pthread_mutex_lock(man->done_persons);
		*(man->done_persons_cnt) += 1;
		pthread_mutex_unlock(man->done_persons);
	}
	if (*(man->done_persons_cnt) == man->num_of_phils)
	{
		*(man->sim_done) = true; // ここは操作が重なっても良いはず
	}
}

void	phil_eat(t_man *man)
{
	take_two_forks(man);
	print_log(man, EAT_MSG);
	man->last_eat_time = get_millisec();
	(man->my_eat_cnt)++;
	check_eat_cnt(man);
	phil_wait(man, man->time_to_eat);
	unlock_two_forks(man);
}

void	phil_sleep(t_man *man)
{
	print_log(man, SLEEP_MSG);
	phil_wait(man, man->time_to_sleep);
}

void	phil_think(t_man *man)
{
	print_log(man, THINK_MSG);
	// phil_wait(man, 100); // 不要かもしれないが続けて同じphilがforkを取らないように
}
