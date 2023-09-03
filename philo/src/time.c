/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:47:36 by jholl             #+#    #+#             */
/*   Updated: 2021/12/09 22:10:27 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	what_time_is_it(void)
{
	long			time;
	struct timeval	current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		return (write_error("gettimeofday return error"));
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	multiple_usleep(long sleeping_time)
{
	long	time_at_call;

	time_at_call = 0;
	time_at_call = what_time_is_it();
	while ((what_time_is_it() - time_at_call) < sleeping_time)
	{
		usleep(100);
	}
}
