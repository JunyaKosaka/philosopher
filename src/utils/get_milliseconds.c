/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_milliseconds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:20:18 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/21 16:58:59 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  get milli seconds  */
long long	get_millisec(void)
{
	struct timeval	time;
	long long		millisec;

	gettimeofday(&time, NULL);
	millisec = (long long)time.tv_sec * 1000 + time.tv_usec / 1000;
	return (millisec);
}
