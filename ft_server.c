/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souhanat <souhanat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 22:56:10 by souhanat          #+#    #+#             */
/*   Updated: 2023/11/22 23:13:25 by souhanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_signal(int sign, siginfo_t *info, void *context)
{
	static char	buff[8];
	static int	i;
	int			j;
	static int	c_pid;
	int			decimal;

	decimal = 0;
	if (c_pid != info->si_pid)
	{
		i = 0;
		ft_bzero(buff, 8);
		c_pid = info->si_pid;
	}
	if (sign == SIGUSR1)
		buff[i++] = '0';
	else if (sign == SIGUSR2)
		buff[i++] = '1';
	if (i == 8)
	{
		j = 0;
		while (j < 8)
			decimal = (decimal * 2) + (buff[j++] - 48);
		ft_putchar(decimal);
		i = 0;
	}
}

int	main(void)
{
	struct sigaction	act;
	int					s_pid;

	act.sa_sigaction = &ft_signal;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	s_pid = getpid();
	ft_putnbr(s_pid);
	ft_putchar('\n');
	while (1)
	{
		pause();
	}
	return (0);
}
