/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrochet <jcrochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 02:30:31 by jcrochet          #+#    #+#             */
/*   Updated: 2025/11/29 22:55:22 by jcrochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "talk.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nb;
	int	signe;

	i = 0;
	nb = 0;
	signe = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signe = signe * -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		nb = nb * 10 + nptr[i] - '0';
		i++;
	}
	return (nb * signe);
}

static char	*ft_itoa_v(long nbr, char *str, int *i)
{
	if (nbr < 0)
	{
		nbr = -nbr;
		str[*i] = '-';
		*i = *i + 1;
	}
	if (nbr >= 10)
		ft_itoa_v(nbr / 10, str, i);
	str[(*i)++] = nbr % 10 + '0';
	return (str);
}

char	*ft_itoa(int n, char *str)
{
	long	nbr;
	int		i;

	i = 0;
	nbr = n;
	str = ft_itoa_v(nbr, str, &i);
	str[i] = '\0';
	return (str);
}

int	get_utf8_size(unsigned char first_byte)
{
	if ((first_byte & 0x80) == 0)
		return (1);
	else if ((first_byte & 0xE0) == 0xC0)
		return (2);
	else if ((first_byte & 0xF0) == 0xE0)
		return (3);
	else if ((first_byte & 0xF8) == 0xF0)
		return (4);
	return (1);
}
