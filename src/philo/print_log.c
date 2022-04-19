/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 23:33:44 by jkosaka           #+#    #+#             */
/*   Updated: 2022/04/18 23:39:45 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  usec: microsecond */
void	print_log(long sec, int usec, int id, char *msg)
{
	printf("%ld %06d %d %s\n", sec, usec, id, msg);
}
