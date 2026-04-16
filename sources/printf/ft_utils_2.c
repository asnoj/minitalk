/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrochet <jcrochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 06:39:28 by jcrochet          #+#    #+#             */
/*   Updated: 2025/11/29 05:00:10 by jcrochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_upper(unsigned int n)
{
	char	*hex;
	int		count;
	char	c;

	hex = "0123456789ABCDEF";
	count = 0;
	if (n >= 16)
		count += ft_puthex_upper(n / 16);
	c = hex[n % 16];
	count += write(1, &c, 1);
	return (count);
}

int	ft_putptr(unsigned long int n, int i)
{
	int		count;
	char	*hex;
	char	c;

	hex = "0123456789abcdef";
	count = 0;
	if (!n)
		return (ft_putstr("(nil)"));
	if (i != 1)
	{
		count += ft_putstr("0x");
		i = 1;
	}
	if (n >= 16)
		count += ft_putptr(n / 16, 1);
	c = hex[n % 16];
	count += write(1, &c, 1);
	return (count);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str || *str == '\0')
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	size_t	i;
	char	*str;

	if (!s)
		return (str = malloc(1));
	i = 0;
	str = (char *)malloc(ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	print_max_char(char **line)
{
	if (*line)
	{
		ft_printf("%s", *line);
		free(*line);
		*line = NULL;
	}
}
