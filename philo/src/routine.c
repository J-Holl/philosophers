/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:34:19 by jholl             #+#    #+#             */
/*   Updated: 2021/12/10 14:51:34 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_check_death(void *void_p)
{
	t_p	*p;

	p = (t_p *)void_p;
	multiple_usleep(p->val->t_die + 1);
	pthread_mutex_lock(&p->val->mutex_write);
	if (((what_time_is_it() - p->record_time_eat) >= p->val->t_die)
		&& !p->val->is_finish)
	{
		p->val->is_finish = 1;
		write_statut(p, "died", DIED);
		return (NULL);
	}
	pthread_mutex_unlock(&p->val->mutex_write);
	return (NULL);
}

int	routine_action(t_p *p)
{
	if (p->id == 1)
	{
		if (!r_eat_no_deadlock(p))
			return (0);
	}
	if (p->id != 1)
	{
		if (!r_eat(p))
			return (0);
	}
	if (!r_sleep(p))
		return (0);
	if (!r_think(p))
		return (0);
	return (1);
}

void	*solo_routine(t_p *p)
{
	pthread_mutex_lock(&p->mutex_l_fork);
	if (!write_statut(p, "has taken a fork", FORK))
	{
		pthread_mutex_unlock(&p->mutex_l_fork);
		return (NULL);
	}
	multiple_usleep(p->val->t_die);
	pthread_mutex_unlock(&p->mutex_l_fork);
	return (NULL);
}

void	*routine(void *void_p)
{
	t_p	*p;

	p = (t_p *)void_p;
	if (p->val->nb_eat == 0)
		return (NULL);
	if (p->id % 2 == 0)
		multiple_usleep(p->val->t_eat / 10);
	while (1)
	{
		if (pthread_create(&p->thr_check_id, NULL, routine_check_death, void_p))
		{
			p->val->is_finish = 3;
			write_error("pthread_create in thread philo failed.");
			return (NULL);
		}
		pthread_detach(p->thr_check_id);
		if (p->val->nb_p == 1)
			return (solo_routine(p));
		if (!routine_action(p))
			return (NULL);
	}
	return (NULL);
}
