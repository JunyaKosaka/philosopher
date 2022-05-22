/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:31:03 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/22 16:34:48 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	return (n > (LONG_MAX - m) / 10);
}

int	ft_atoi(const char *str)
{
	long	ret;
	int		sign;

	sign = 1;
	ret = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		sign = 44 - *str;
		str++;
	}
	while (ft_isdigit(*str))
	{
		if (is_over(ret, *str - '0'))
			return (-1);
		ret = ret * 10 + (*str - '0');
		str++;
	}
	return (ret * sign);
}
