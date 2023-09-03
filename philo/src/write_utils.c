/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 00:07:14 by jholl             #+#    #+#             */
/*   Updated: 2021/12/07 18:54:54 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	count_digit(long nbr)
{
	int	ret;

	ret = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= 10;
		ret++;
	}
	return (ret);
}

int	insert_long_in_string(long nbr, char *s)
{
	int	nbr_digits;
	int	index;

	nbr_digits = count_digit(nbr);
	s[nbr_digits] = ' ';
	index = nbr_digits;
	while (--nbr_digits > -1)
	{
		s[nbr_digits] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (index);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}
