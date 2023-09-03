/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:55:35 by jholl             #+#    #+#             */
/*   Updated: 2021/12/10 15:14:13 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	write_error(char *s)
{
	write(2, s, ft_strlen(s));
	return (-1);
}

int	other_statut(t_p *p, char s[100])
{
	if (p->val->is_finish)
	{
		pthread_mutex_unlock(&p->val->mutex_write);
		return (0);
	}
	ft_putstr(s);
	pthread_mutex_unlock(&p->val->mutex_write);
	return (1);
}

int	die_statut(t_p *p, char s[100])
{
	ft_putstr(s);
	pthread_mutex_unlock(&p->val->mutex_write);
	return (1);
}

int	eat_statut(t_p *p, char s[100])
{
	if (p->val->is_finish)
	{
		pthread_mutex_unlock(&p->val->mutex_write);
		return (0);
	}
	ft_putstr(s);
	p->record_time_eat = what_time_is_it();
	p->nb_i_eat++;
	if (p->val->nb_eat == p->nb_i_eat)
		p->val->finish_eat++;
	if (p->val->finish_eat == p->val->nb_p && p->val->nb_eat >= 0)
	{
		p->val->is_finish = 2;
		pthread_mutex_unlock(&p->val->mutex_write);
		return (0);
	}
	pthread_mutex_unlock(&p->val->mutex_write);
	return (1);
}

/*
** buf[100] cause message statut is: a long, an int, and a string.
** On our correction architecture;
** long: 19 max digit, int: 9max digit and max string is 16 char
** for fork. ~50 max.
*/

int	write_statut(t_p *p, char *s, int statut)
{
	char	buf[100];
	long	timestamp;
	int		actual_index;
	int		i;

	memset(buf, 0, 100);
	if (statut != DIED)
		pthread_mutex_lock(&p->val->mutex_write);
	timestamp = what_time_is_it() - p->val->t_simulation_start;
	actual_index = 0;
	actual_index = 1 + insert_long_in_string(timestamp, buf);
	actual_index += 1 + insert_long_in_string((long)p->id, &buf[actual_index]);
	i = -1;
	while (s[++i])
		buf[actual_index + i] = s[i];
	actual_index += i;
	buf[actual_index] = '\n';
	buf[actual_index + 1] = '\0';
	if (statut == 1)
		return (eat_statut(p, buf));
	if (statut == 2)
		return (other_statut(p, buf));
	return (die_statut(p, buf));
}
