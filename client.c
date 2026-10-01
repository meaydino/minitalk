/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meaydino <meaydino@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 12:07:00 by meaydino          #+#    #+#             */
/*   Updated: 2026/10/01 14:46:55 by meaydino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack = 0;

static void	handle_ack(int sig)
{
	if (sig == SIGUSR1)
		g_ack = 1;
	else if (sig == SIGUSR2)
		g_ack = 2;
}

static int	pid_check(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	send_char(pid_t pid, unsigned char c)
{
	int	bit;
	int	timeout;

	bit = 0;
	while (bit < 8)
	{
		g_ack = 0;
		if ((c >> bit) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		timeout = 0;
		while (!g_ack)
		{
			usleep(10);
			timeout++;
			if (timeout > 300000)
			{
				ft_putstr_fd("Error: Server response timeout.\n", 2);
				exit(1);
			}
		}
		bit++;
	}
}

static void	init_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_ack;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	int		i;

	if (argc != 3 || !pid_check(argv[1]))
	{
		ft_putstr_fd("Usage: ./client <server_pid> <string_to_send>\n", 2);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0 || kill(server_pid, 0) == -1)
	{
		ft_putstr_fd("Error: Invalid or non-existent server PID.\n", 2);
		return (1);
	}
	init_signals();
	i = 0;
	while (argv[2][i])
		send_char(server_pid, argv[2][i++]);
	send_char(server_pid, '\0');
	if (g_ack == 2)
		ft_putstr_fd("Success: Message received completely by server.\n", 1);
	return (0);
}
