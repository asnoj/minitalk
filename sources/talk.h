/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   talk.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrochet <jcrochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 23:41:07 by jcrochet          #+#    #+#             */
/*   Updated: 2025/11/30 00:39:46 by jcrochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TALK_H
# define TALK_H

# include "printf/ft_printf.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BIT_ZERO SIGUSR1
# define BIT_ONE SIGUSR2
# define C_NBR_MAX 100

# ifndef WAIT
#  define WAIT 700
# endif

typedef struct s_data
{
	unsigned char	curr_c;
	int				bit_count;
	pid_t			client_pid;
	int				is_pid;
	int				pid;
	size_t			charnbr;

}					t_data;

int					ft_atoi(const char *nptr);
char				*ft_itoa(int n, char *str);
int					bi_to_dec(int bi);
void				handle_server_response(int signal);
int					get_utf8_size(unsigned char first_byte);
char				*ft_strdup(char *s);
size_t				ft_strlen(char *str);
void				print_max_char(char **line);
void				print_max_char(char **line);
void				ft_line(int bool, char c);

#endif
