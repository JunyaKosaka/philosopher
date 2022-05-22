/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:42:32 by jkosaka           #+#    #+#             */
/*   Updated: 2022/05/22 15:17:37 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	idx;

	idx = 0;
	while (s[idx])
		idx++;
	return (idx);
}

static void	write_fd(char **s, int fd, size_t len)
{
	write(fd, *s, len);
	*s += len;
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write_fd(&s, fd, len % INT_MAX);
	len /= INT_MAX;
	while (len--)
		write_fd(&s, fd, INT_MAX);
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*pt_1;
	unsigned char	*pt_2;

	pt_1 = (unsigned char *)s1;
	pt_2 = (unsigned char *)s2;
	while ((*pt_1 == *pt_2) && (*pt_1 != '\0'))
	{
		pt_1++;
		pt_2++;
	}
	return (*pt_1 - *pt_2);
}
