/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souhanat <souhanat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:38:00 by yoamzil           #+#    #+#             */
/*   Updated: 2023/11/22 22:18:22 by souhanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_usr(int sign, siginfo_t *info, void *context)
{
	static char	buffer[8];
	static int	index;
	static int	client_pid;
	int			decimal;
	int			j;

	decimal = 0;
	if (client_pid != info->si_pid)
	{
		index = 0;
		ft_bzero(buffer, 8);
		client_pid = info->si_pid;
	}
	if (sign == SIGUSR1)
		buffer[index++] = '0';
	else if (sign == SIGUSR2)
		buffer[index++] = '1';
	if (index == 8)
	{
		j = 0;
		while (j < 8)
			decimal = (decimal * 2) + (buffer[j++] - 48);
		ft_putchar(decimal);
		index = 0;
	}
}

int	main(void)
{
	struct sigaction	action;
	int					server_pid;

	action.sa_sigaction = &sig_usr;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	server_pid = getpid();
	ft_putnbr(server_pid);
	ft_putchar('\n');
	while (1)
	{
		pause();
	}
	return (0);
}
