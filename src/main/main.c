/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:02:39 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/23 15:37:27 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat] */
static int	input_info(t_info *info, int argc, char **argv)
{
	info->num_of_phils = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->must_eat_cnt = -1;
	if (argc == 6)
	{
		info->must_eat_cnt = ft_atoi(argv[5]);
		if (info->must_eat_cnt <= 0)
			return (1);
	}
	if (info->num_of_phils <= 0 || info->time_to_die <= 0 || \
			info->time_to_eat < 0 || info->time_to_sleep < 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || 6 < argc)
		return (error_handler(USAGE_MSG));
	info = (t_info){0};
	if (input_info(&info, argc, argv))
		return (error_handler(USAGE_MSG));
	philosopher(&info);
	return (0);
}
