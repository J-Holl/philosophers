/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 22:25:56 by jholl             #+#    #+#             */
/*   Updated: 2021/12/09 17:48:33 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_p_and_val(t_p *p, t_val *val)
{
	int	i;

	i = 0;
	val->is_finish = 0;
	val->finish_eat = 0;
	pthread_mutex_init(&val->mutex_write, NULL);
	val->t_simulation_start = what_time_is_it();
	while (i < val->nb_p)
	{
		p[i].record_time_eat = val->t_simulation_start;
		p[i].val = val;
		p[i].nb_i_eat = 0;
		p[i].id = i + 1;
		p[i].mutex_r_fork = NULL;
		pthread_mutex_init(&p[i].mutex_l_fork, NULL);
		if (val->nb_p == 1)
			return ;
		if (val->nb_p - 1 != i)
			p[i].mutex_r_fork = &p[i + 1].mutex_l_fork;
		if (val->nb_p - 1 == i)
			p[i].mutex_r_fork = &p[0].mutex_l_fork;
		i++;
	}
}
