/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souhanat <souhanat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 22:56:02 by souhanat          #+#    #+#             */
/*   Updated: 2023/11/22 23:22:11 by souhanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_change(char c, int server_pid)
{
	char	str[9];
	int		i;

	i = 7;
	str[8] = '\0';
	while (c != 0)
	{
		str[i] = c % 2 + 48;
		c = c / 2;
		i--;
	}
	while (c == 0 && i >= 0)
		str[i--] = 48;
	i = 0;
	while (str[i])
	{
		if (str[i] == '0')
			kill(server_pid, SIGUSR1);
		else if (str[i] == '1')
			kill(server_pid, SIGUSR2);
		usleep(100);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int		server_pid;
	char	*str;
	int		i;

	if (argc != 3)
	{
		write(1, "Wrong arguments.\n", 35);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	str = argv[2];
	i = 0;
	if (server_pid < 2)
		return (1);
	if (argc == 3)
	{
		while (str[i])
		{
			ft_change(str[i], server_pid);
			i++;
		}
	}
	return (0);
}
