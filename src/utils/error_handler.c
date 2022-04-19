/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkosaka <jkosaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:39:51 by jkosaka           #+#    #+#             */
/*   Updated: 2022/04/15 17:03:52 by jkosaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  return 1  */
int	error_handler(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	return (1);
}
