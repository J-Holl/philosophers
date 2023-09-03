/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:57:43 by jholl             #+#    #+#             */
/*   Updated: 2021/12/10 15:27:16 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_pos_int(char *s, t_val *val, int j)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		res = (res * 10) + (s[i] - '0');
		i++;
	}
	if (res > INT_MAX || (res == 0 && j != 5))
		return (0);
	if (j == 1)
		val->nb_p = res;
	if (j == 2)
		val->t_die = res;
	if (j == 3)
		val->t_eat = res;
	if (j == 4)
		val->t_sleep = res;
	if (j == 5)
		val->nb_eat = res;
	return (1);
}

int	check_args(int ac, char **av, t_val *val)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (write_error("Wrong numbers of args."));
	i = 1;
	val->nb_eat = -1;
	while (i < ac)
	{
		if (!is_pos_int(av[i], val, i))
			return (write_error("0 < your_val <= INT_MAX, nb_eat can be 0."));
		i++;
	}
	return (1);
}

int	start_philo(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->val->nb_p)
	{
		if (pthread_create(&p[i].thr_id, NULL, routine, &p[i]))
			return (write_error("pthread_create error."));
		i++;
	}
	return (1);
}

void	end_philo(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->val->nb_p)
	{
		pthread_join(p[i].thr_id, NULL);
		i++;
	}
	multiple_usleep(p->val->t_die * 2);
	pthread_mutex_lock(&p->val->mutex_write);
	pthread_mutex_unlock(&p->val->mutex_write);
	pthread_mutex_destroy(&p->val->mutex_write);
	i = 0;
	while (i < p->val->nb_p)
	{
		pthread_mutex_destroy(&p[i].mutex_l_fork);
		i++;
	}
	free(p);
}

int	main(int ac, char **av)
{
	t_val	val;
	t_p		*p;

	if (check_args(ac, av, &val) == -1)
	{
		write_error("[number of philo] [time to die] [time to eat]");
		write_error("[time to sleep] ([meals before stop simulation])\n");
		return (-1);
	}
	p = malloc(sizeof(t_p) * val.nb_p);
	if (!p)
		return (write_error("Malloc error."));
	memset(p, 0, (sizeof(t_p) * val.nb_p));
	init_p_and_val(p, &val);
	start_philo(p);
	end_philo(p);
	return (0);
}
