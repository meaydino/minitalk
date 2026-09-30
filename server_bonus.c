/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meaydino <meaydino@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 12:07:30 by meaydino          #+#    #+#             */
/*   Updated: 2026/09/30 14:57:06 by meaydino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	process_char(unsigned char *c, pid_t *pid, int *bit)
{
	*bit = 0;
	if (*c == '\0')
	{
		write(1, "\n", 1);
		kill(*pid, SIGUSR2);
		*pid = 0;
		*c = 0;
		return (1);
	}
	write(1, c, 1);
	*c = 0;
	return (0);
}

static void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static int				bit_index = 0;
	static unsigned char	current_char = 0;
	static pid_t			client_pid = 0;

	(void)context;
	if (client_pid == 0)
		client_pid = info->si_pid;
	if (info->si_pid != client_pid)
		return ;
	if (sig == SIGUSR2)
		current_char |= (1 << bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		if (process_char(&current_char, &client_pid, &bit_index))
			return ;
	}
	kill(client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr_fd("Server (Bonus) PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
