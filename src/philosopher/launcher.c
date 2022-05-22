/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:01:17 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/22 12:45:49 by jkosaka          ###   ########.fr       */
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

/*  philosopher takes the first fork  */
void	first_fork(t_man *man)
{
	if (man->id & 1)
	{
		usleep(200);
		pthread_mutex_lock(man->left_fork);	
	}
	else
	{
		pthread_mutex_lock(man->right_fork);	
	}
	print_log(man, FORK_MSG);
}

/*  philosopher takes the second fork  */
void	second_fork(t_man *man)
{
	if (man->id & 1)
	{
		pthread_mutex_lock(man->right_fork);	
	}
	else
	{
		usleep(200); // いらないような
		pthread_mutex_lock(man->left_fork);	
	}
	print_log(man, FORK_MSG);
}

void	take_two_forks(t_man *man)
{
	first_fork(man);
	second_fork(man);
}

void	unlock_two_forks(t_man *man)
{
	pthread_mutex_unlock(man->right_fork);
	pthread_mutex_unlock(man->left_fork);
}

/*  check if eat count reached must_eat_cnt  */
void	check_eat_cnt(t_man *man)
{
	if (man->my_eat_cnt == man->must_eat_cnt)
	{
		printf("== 88 %d %d %d\n", man->id, *(man->done_persons_cnt), man->num_of_phils);
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

void	*loop_thread(void *p)
{
	t_man	*man;
	int		cnt;

	man = p;
	cnt = 0;
	// man->last_eat_time = get_millisec(); // init_menでやる
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
