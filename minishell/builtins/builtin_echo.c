/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:27:04 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/04 16:32:48 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	check_option(char *option)
{
	int	len;
	int	i;

	len = ft_strlen(option);
	i = 2;
	if (!ft_strncmp(option, "-n", ft_strlen("-n")))
	{
		while (i < len)
		{
			if (option[i] != 'n')
				return (0);
			i++;
		}
		if (i == len)
			return (1);
	}
	return (0);
}

void	builtin_echo(t_process *process, int fd)
{
	int		i;
	int		flag;

	i = 1;
	flag = 1;
	while (process->cmd[i])
	{
		if (flag && !check_option(process->cmd[i]))
		{
			ft_putstr_fd(process->cmd[i], fd);
			if (process->cmd[i + 1])
				ft_putstr_fd(" ", fd);
			flag = 0;
		}
		else if (!flag)
		{
			ft_putstr_fd(process->cmd[i], fd);
			if (process->cmd[i + 1])
				ft_putstr_fd(" ", fd);
		}
		i++;
	}
	if (i == 1 || !check_option(process->cmd[1]))
		ft_putstr_fd("\n", fd);
}
