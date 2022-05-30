/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 13:36:54 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/30 22:43:33 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	done_simulation(t_man *man)
{
	bool	done;

	pthread_mutex_lock(man->sim_done_mutex);
	done = *(man->sim_done);
	pthread_mutex_unlock(man->sim_done_mutex);
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
		if (waiting_time - (cur_time - start) > 5)
			usleep(3000);
		usleep(500);
		cur_time = get_millisec();
		if (man->time_to_die <= cur_time - man->last_eat_time)
		{
			print_log(man, DIED_MSG);
			return ;
		}
	}
}

/*  philosopher eats  */
void	phil_eat(t_man *man)
{
	long long	cur_time;

	take_two_forks(man);
	cur_time = get_millisec();
	if (man->time_to_die <= cur_time - man->last_eat_time)
	{
		print_log(man, DIED_MSG);
		unlock_two_forks(man);
		return ;
	}
	print_log(man, EAT_MSG);
	pthread_mutex_lock(man->time_keeper_mutex);
	man->last_eat_time = get_millisec();
	pthread_mutex_unlock(man->time_keeper_mutex);
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
	int	diff;

	print_log(man, THINK_MSG);
	if (man->num_of_phils & 1)
	{
		diff = man->time_to_eat / ((man->num_of_phils - 1) / 2);
		phil_wait(man, man->time_to_eat + diff - man->time_to_sleep - 1);
	}
	else
		phil_wait(man, man->time_to_eat - man->time_to_sleep - 1);
}
