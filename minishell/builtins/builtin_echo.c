/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:27:04 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/17 20:51:58 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	check_option(char *option)
{
	int	len;
	int	i;

	len = ft_strlen(option);
	i = 2;
	if (!ft_strncmp(option, "-n", ft_strlen("-n")) && len >= 2 )
	{
		while (i < len)
		{
			if (option[i] != 'n')
				return (0);
			i++;
		}
	}
	if (i == len)
		return (1);
	return (0);
}

void	builtin_echo(t_process *process)
{
	int		i;
	int		flag;

	i = 1;
	flag = 1;
	while (process->cmd[i])
	{
		if (flag && !check_option(process->cmd[i]))
		{
			write(1, process->cmd[i], ft_strlen(process->cmd[i]));
			if (process->cmd[i + 1])
				write(1, " ", 1);
			flag = 0;
		}
		else if (!flag)
		{
			write(1, process->cmd[i], ft_strlen(process->cmd[i]));
			if (process->cmd[i + 1])
				write(1, " ", 1);
		}
		i++;
	}
	if (i == 1 || !check_option(process->cmd[1]))
		write (1, "\n", 1);
}
