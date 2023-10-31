/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/31 20:22:00 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void	check_builtins(t_process *process, t_env *env, int fd)
{
	if (process->cmd[0])
	{
		if (!ft_strncmp(process->cmd[0], "echo", ft_strlen("echo")))
			builtin_echo(process, fd);
		else if (!ft_strncmp(process->cmd[0], "cd", ft_strlen("cd")))
			builtin_cd(process);
		else if (!ft_strncmp(process->cmd[0], "pwd", ft_strlen("pwd")))
			builtin_pwd(fd);
		else if (!ft_strncmp(process->cmd[0], "env", ft_strlen("env")))
			builtin_env(process, env, fd);
		else if (!ft_strncmp(process->cmd[0], "export", ft_strlen("export")))
			builtin_export(process, env, fd);
		else if (!ft_strncmp(process->cmd[0], "unset", ft_strlen("unset")))
			builtin_unset(process, env, fd);
		else if (!ft_strncmp(process->cmd[0], "exit", ft_strlen("exit")))
			builtin_exit(process);
	}
	return ;
}

int	is_builtin(t_process *process)
{
	if (process->cmd[0])
	{
		if (!ft_strncmp(process->cmd[0], "echo", ft_strlen("echo")))
			return (1);
		else if (!ft_strncmp(process->cmd[0], "cd", ft_strlen("cd")))
			return (1);
		else if (!ft_strncmp(process->cmd[0], "pwd", ft_strlen("pwd")))
			return (1);
		else if (!ft_strncmp(process->cmd[0], "export", ft_strlen("export")))
			return (1);
		else if (!ft_strncmp(process->cmd[0], "unset", ft_strlen("unset")))
			return (1);
		else if (!ft_strncmp(process->cmd[0], "env", ft_strlen("env")))
			return (1);
		else if (!ft_strncmp(process->cmd[0], "exit", ft_strlen("exit")))
			return (1);
	}
	return (0);
}
