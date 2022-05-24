/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 13:36:54 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/24 20:17:32 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	done_simulation(t_man *man)
{
	bool	done;

	pthread_mutex_lock(man->baton);
	done = *(man->sim_done);
	pthread_mutex_unlock(man->baton);
	return (done);
}

/*  wait until waiting_time passes  */
void	phil_wait(t_man *man, int waiting_time)
{
	long long	start;
	long long	cur_time;

	start = get_millisec();
	cur_time = start;
	while ((done_simulation(man) == false) && (cur_time - start < waiting_time))
	{
		cur_time = get_millisec();
		if (man->time_to_die <= cur_time - man->last_eat_time)
		{
			print_log(man, DIED_MSG);
			return ;
		}
		usleep(200);
	}
}

/*  philosopher eats  */
void	phil_eat(t_man *man)
{
	long long	cur_time;

	take_two_forks(man);
	cur_time = get_millisec();
	if (cur_time - man->last_eat_time >= man->time_to_die)
	{
		print_log(man, DIED_MSG);
		return ;
	}
	man->last_eat_time = get_millisec();
	print_log(man, EAT_MSG);
	phil_wait(man, man->time_to_eat);
	(man->my_eat_cnt)++;
	unlock_two_forks(man);
}

/*  philosopher sleeps  */
void	phil_sleep(t_man *man)
{
	print_log(man, SLEEP_MSG);
	phil_wait(man, man->time_to_sleep);
}

/*  philosopher thinks  */
void	phil_think(t_man *man)
{
	print_log(man, THINK_MSG);
}
