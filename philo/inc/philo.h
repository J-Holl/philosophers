/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:03:00 by jholl             #+#    #+#             */
/*   Updated: 2021/12/09 22:11:24 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

# define DIED 0
# define EAT 1
# define FORK 2
# define THINK 2
# define SLEEP 2

typedef struct s_val
{
	int				nb_p;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_eat;
	int				is_finish;
	int				finish_eat;
	long			t_simulation_start;
	pthread_mutex_t	mutex_write;
}				t_val;

typedef struct s_p
{
	int				id;
	int				nb_i_eat;
	long			record_time_eat;
	pthread_t		thr_id;
	pthread_t		thr_check_id;
	pthread_mutex_t	mutex_l_fork;
	pthread_mutex_t	mutex_time;
	pthread_mutex_t	*mutex_r_fork;
	t_val			*val;
}				t_p;

//main
int		is_finish(t_p *p);

//routine
void	*routine(void *void_p);
void	*routine_check_death(void *void_p);

//action
int		r_eat_no_deadlock(t_p *p);
int		r_think(t_p *p);
int		r_sleep(t_p *p);
int		r_eat(t_p *p);

//time
long	what_time_is_it(void);
void	multiple_usleep(long sleeping_time);

//init
void	init_p_and_val(t_p *p, t_val *val);

//write
int		write_error(char *s);	
int		write_statut(t_p *p, char *s, int statut);

//write_utils
int		count_digit(long nbr);
int		insert_long_in_string(long nbr, char *s);
int		ft_strlen(char *s);
void	ft_putstr(char *s);

#endif
