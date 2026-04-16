/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrochet <jcrochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 05:37:31 by jcrochet          #+#    #+#             */
/*   Updated: 2025/11/30 00:37:17 by jcrochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_convert(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (c == 'p')
		return (ft_putptr((unsigned long int)va_arg(args, void *), 0));
	if (c == 'd')
		return (ft_putnbr(va_arg(args, int)));
	if (c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (c == 'u')
		return (ft_putunsignnbr(va_arg(args, unsigned int)));
	if (c == 'x')
		return (ft_puthex_lower(va_arg(args, unsigned int)));
	if (c == 'X')
		return (ft_puthex_upper(va_arg(args, unsigned int)));
	if (c == '%')
		return (write(1, "%", 1), 1);
	return (write(1, &c, 1), 1);
}

int	ft_printf(const char *form, ...)
{
	int		i;
	va_list	args;

	i = 0;
	va_start(args, form);
	while (*form)
	{
		if (*form == '%')
			i += ft_convert(*++form, args);
		else
		{
			write(1, form, 1);
			i++;
		}
		form++;
	}
	va_end(args);
	return (i);
}

void	ft_line(int bool, char c)
{
	static char	*line = NULL;
	size_t		i;
	char		*dst;

	if (!line)
	{
		line = ft_strdup("");
		if (!line)
			return ;
	}
	if (0 == bool)
		return ((void)print_max_char(&line));
	if (ft_strlen(line) >= C_NBR_MAX)
		(print_max_char(&line), line = ft_strdup(""));
	dst = malloc(ft_strlen(line) + 2);
	if (!dst)
		return ;
	i = -1;
	while (line[++i])
		dst[i] = line[i];
	dst[i] = c;
	dst[i + 1] = '\0';
	free(line);
	line = ft_strdup(dst);
	free(dst);
}

//#include <stdio.h>
//#include <limits.h>
//int	main(void)
//{
//	ft_printf(NULL);
//	printf(NULL);
//}

// #include <stdio.h>
// #include <limits.h>
// #include "ft_printf.h"
// int main(void)
// {
//     int ret1, ret2;
//     char *str_null = NULL;
//     void *ptr_null = NULL;
//     void *ptr_valid = (void *)0xdeadbeef;
//     unsigned int uvals[] = {0, 1, UINT_MAX, 123456789};
//     int ivals[] = {INT_MIN, INT_MAX, -1, 0, 42};
//     char chars[] = {'A', 'z', '\0', '%'};
//     char *strings[] = {"Hello", "", str_null};

//     // Test simple conversions
//     for (int i = 0; i < 4; i++)
//     {
//         ret1 = printf("printf   : %c\n", chars[i]);
//         ret2 = ft_printf("ft_printf: %c\n", chars[i]);
//         if (ret1 != ret2) printf("Mismatch!\n");
//     }

//     for (int i = 0; i < 3; i++)
//     {
//         ret1 = printf("printf   : %s\n", strings[i]);
//         ret2 = ft_printf("ft_printf: %s\n", strings[i]);
//         if (ret1 != ret2) printf("Mismatch!\n");
//     }

//     for (int i = 0; i < 5; i++)
//     {
//         ret1 = printf("printf   : %d %i\n", ivals[i], ivals[i]);
//         ret2 = ft_printf("ft_printf: %d %i\n", ivals[i], ivals[i]);
//         if (ret1 != ret2) printf("Mismatch!\n");
//     }

//   for (int i = 0; i < 4; i++)
//   {
//    ret1 = printf("printf   : %u %x %X\n", uvals[i], uvals[i], uvals[i]);
//    ret2 = ft_printf("ft_printf: %u %x %X\n", uvals[i], uvals[i], uvals[i]);
//    if (ret1 != ret2) printf("Mismatch!\n");
//   }
//     // Test pointeurs
//     ret1 = printf("printf   : %p %p %p\n", ptr_null, ptr_valid, str_null);
//     ret2 = ft_printf("ft_printf: %p %p %p\n", ptr_null, ptr_valid, str_null);
//     if (ret1 != ret2) printf("Mismatch!\n");

//     // Test %% et combinaisons
//     ret1 = printf("printf   : %% %% %%\n");
//     ret2 = ft_printf("ft_printf: %% %% %%\n");
//     if (ret1 != ret2) printf("Mismatch!\n");

//     // Test combiné complexe
// ret1 = printf("printf   : %c %s %d %i %u %x %X %p %%\n",
// 'Z', str_null, INT_MIN, INT_MAX, UINT_MAX, 0xdeadbeef, 0xDEADBEEF, ptr_null);
// ret2 = ft_printf("ft_printf: %c %s %d %i %u %x %X %p %%\n",
// 'Z', str_null, INT_MIN, INT_MAX, UINT_MAX, 0xdeadbeef, 0xDEADBEEF, ptr_null);
//     if (ret1 != ret2) printf("Mismatch!\n");
//     // Test chaîne longue avec % consécutifs
//     ret1 = printf("printf   : %%%%%%%% %%%% %%%% %c %s\n", 'X', "TEST");
//     ret2 = ft_printf("ft_printf: %%%%%%%% %%%% %%%% %c %s\n", 'X', "TEST");
//     if (ret1 != ret2) printf("Mismatch!\n");

//     return 0;
// }
