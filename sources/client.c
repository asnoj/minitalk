/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrochet <jcrochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 03:05:54 by jcrochet          #+#    #+#             */
/*   Updated: 2025/11/29 05:04:22 by jcrochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "talk.h"

int		g_received = 0;

void	handle_server_response(int signal)
{
	(void)signal;
	g_received = 1;
}

void	send_bit(int server_pid, int bit)
{
	if (0 == bit)
		kill(server_pid, BIT_ZERO);
	else
		kill(server_pid, BIT_ONE);
	usleep(WAIT);
}

void	send_message(int server_pid, char *message)
{
	ssize_t			i;
	int				j;
	unsigned char	c;

	i = 0;
	while (message[i])
	{
		c = (unsigned char)message[i];
		j = 7;
		while (j >= 0)
		{
			send_bit(server_pid, (c >> j) & 1);
			j--;
		}
		i++;
	}
	j = 7;
	while (j >= 0)
	{
		send_bit(server_pid, 0);
		j--;
	}
}

int	main(int argc, char **argv)
{
	int					server_pid;
	char				pid_str[20];
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_printf("Invalid PID\n");
		exit(EXIT_FAILURE);
	}
	sa.sa_handler = handle_server_response;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	ft_itoa(getpid(), pid_str);
	send_message(server_pid, pid_str);
	send_message(server_pid, argv[2]);
	while (!g_received)
		pause();
	return (0);
}
