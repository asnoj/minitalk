/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrochet <jcrochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 00:39:11 by jcrochet          #+#    #+#             */
/*   Updated: 2025/11/30 00:40:36 by jcrochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "talk.h"

t_data	*g_dataa;

void	re_init(int bool)
{
	int	i;

	i = 0;
	if (1 == bool)
	{
		g_dataa->is_pid = 1;
		g_dataa->pid = 0;
		g_dataa->client_pid = 0;
	}
	else
		g_dataa->is_pid = 0;
	ft_line(0, g_dataa->curr_c);
	g_dataa->charnbr = 0;
	g_dataa->bit_count = 0;
	g_dataa->curr_c = 0;
}

void	handle_pid(int signal)
{
	int	bit;

	bit = 0;
	if (signal == BIT_ZERO)
		bit = 0;
	else if (signal == BIT_ONE)
		bit = 1;
	g_dataa->curr_c = (g_dataa->curr_c << 1) | bit;
	g_dataa->bit_count++;
	if (8 == g_dataa->bit_count)
	{
		if (g_dataa->curr_c == '\0')
		{
			g_dataa->is_pid = 0;
			g_dataa->bit_count = 0;
			g_dataa->curr_c = 0;
			return ;
		}
		g_dataa->pid = g_dataa->pid * 10 + (g_dataa->curr_c - '0');
		g_dataa->bit_count = 0;
		g_dataa->curr_c = 0;
	}
}

void	handle_signal(int signal)
{
	int	bit;

	bit = 0;
	if (1 == g_dataa->is_pid)
	{
		handle_pid(signal);
		return ;
	}
	if (signal == BIT_ZERO)
		bit = 0;
	else if (signal == BIT_ONE)
		bit = 1;
	g_dataa->curr_c = (g_dataa->curr_c << 1) | bit;
	g_dataa->bit_count++;
	if (8 == g_dataa->bit_count)
	{
		if (g_dataa->curr_c == '\0')
		{
			(ft_line(0, g_dataa->curr_c), kill(g_dataa->pid, SIGUSR1));
			return ((void)re_init(1));
		}
		ft_line(1, g_dataa->curr_c);
		g_dataa->bit_count = 0;
		g_dataa->curr_c = 0;
	}
}

void	handle_exit(int signal)
{
	(void)signal;
	if (g_dataa)
	{
		free(g_dataa);
		g_dataa = NULL;
	}
	ft_printf("\n✓ Server stopped cleanly\n");
	exit(0);
}

int	main(void)
{
	struct sigaction	sa;
	struct sigaction	sa_int;

	ft_printf("%d\n", getpid());
	g_dataa = malloc(sizeof(t_data));
	if (!g_dataa)
		return (1);
	g_dataa->charnbr = 0;
	g_dataa->curr_c = 0;
	g_dataa->bit_count = 0;
	g_dataa->pid = 0;
	g_dataa->is_pid = 1;
	sa.sa_handler = handle_signal;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sa_int.sa_handler = handle_exit;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	while (1)
		pause();
	return (0);
}
