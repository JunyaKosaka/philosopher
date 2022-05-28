/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:31:03 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/28 22:07:57 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_isspace(int c)
{
	return (('\t' <= c && c <= '\r') || c == ' ');
}

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

static bool	is_over(long n, int m)
{
	return (n > (INT_MAX - m) / 10);
}

/*  handle only none negative int  */
int	phil_atoi(const char *str)
{
	long	ret;

	ret = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		if (is_over(ret, *str - '0'))
			return (-1);
		ret = ret * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (ret);
}
