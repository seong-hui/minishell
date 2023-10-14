/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:27:04 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/13 13:34:50 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_option(char **token)
{
	char	**cmd;
	int		cmd_cnt;

	if (!ft_strncmp(cmd[1], "-n", ft_strlen("-n")))
		return (1);
	return (0);
}

void	builtin_echo(t_process *process)
{
	int		i;

	i = 1;
	if (check_option(process->cmd[1]))
		i++;
	while (process->cmd[i])
	{
		write(1, process->cmd[i], ft_strlen(process->cmd[i]));
		if (process->cmd[i+1])
			write(1, " ", 1);
		i++;
	}
	if (!check_option(process->cmd[1]))
			write(1, "\n", 1);
}
