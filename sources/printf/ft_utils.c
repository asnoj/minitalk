/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrochet <jcrochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 06:34:22 by jcrochet          #+#    #+#             */
/*   Updated: 2025/10/26 20:01:14 by jcrochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	i;

	if (!s)
		return (write(1, "(null)", 6));
	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
	return (i);
}

int	ft_putnbr(int n)
{
	long	num;
	int		count;
	char	c;

	num = n;
	count = 0;
	if (num < 0)
	{
		count += write(1, "-", 1);
		num = -num;
	}
	if (num >= 10)
		count += ft_putnbr(num / 10);
	c = (num % 10) + '0';
	count += write(1, &c, 1);
	return (count);
}

int	ft_putunsignnbr(unsigned int n)
{
	int		count;
	char	c;

	count = 0;
	if (n >= 10)
		count += ft_putunsignnbr(n / 10);
	c = (n % 10) + '0';
	count += write(1, &c, 1);
	return (count);
}

int	ft_puthex_lower(unsigned int n)
{
	char	*hex;
	int		count;
	char	c;

	hex = "0123456789abcdef";
	count = 0;
	if (n >= 16)
		count += ft_puthex_lower(n / 16);
	c = hex[n % 16];
	count += write(1, &c, 1);
	return (count);
}
