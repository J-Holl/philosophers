/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:40:53 by jholl             #+#    #+#             */
/*   Updated: 2021/12/07 15:49:27 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	r_eat_no_deadlock(t_p *p)
{
	pthread_mutex_lock(&p->mutex_l_fork);
	if (!write_statut(p, "has taken a fork", FORK))
	{
		pthread_mutex_unlock(&p->mutex_l_fork);
		return (0);
	}
	pthread_mutex_lock(p->mutex_r_fork);
	if (!write_statut(p, "has taken a fork", FORK))
	{
		pthread_mutex_unlock(&p->mutex_l_fork);
		pthread_mutex_unlock(p->mutex_r_fork);
		return (0);
	}
	if (!write_statut(p, "is eating", EAT))
	{
		pthread_mutex_unlock(&p->mutex_l_fork);
		pthread_mutex_unlock(p->mutex_r_fork);
		return (0);
	}
	multiple_usleep(p->val->t_eat);
	pthread_mutex_unlock(&p->mutex_l_fork);
	pthread_mutex_unlock(p->mutex_r_fork);
	return (1);
}

int	r_eat(t_p *p)
{
	pthread_mutex_lock(p->mutex_r_fork);
	if (!write_statut(p, "has taken a fork", FORK))
	{
		pthread_mutex_unlock(p->mutex_r_fork);
		return (0);
	}
	pthread_mutex_lock(&p->mutex_l_fork);
	if (!write_statut(p, "has taken a fork", FORK))
	{
		pthread_mutex_unlock(p->mutex_r_fork);
		pthread_mutex_unlock(&p->mutex_l_fork);
		return (0);
	}
	if (!write_statut(p, "is eating", EAT))
	{
		pthread_mutex_unlock(p->mutex_r_fork);
		pthread_mutex_unlock(&p->mutex_l_fork);
		return (0);
	}
	multiple_usleep(p->val->t_eat);
	pthread_mutex_unlock(p->mutex_r_fork);
	pthread_mutex_unlock(&p->mutex_l_fork);
	return (1);
}

int	r_sleep(t_p *p)
{
	if (!write_statut(p, "is sleeping", SLEEP))
	{
		return (0);
	}
	multiple_usleep(p->val->t_sleep);
	return (1);
}

int	r_think(t_p *p)
{
	if (!write_statut(p, "is thinking", THINK))
	{
		return (0);
	}
	return (1);
}
