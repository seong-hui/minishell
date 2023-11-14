/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:43:19 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/14 19:51:52 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void	check_builtins(t_process *process, t_env **env, int fd, t_excute e_info)
{
	if (process->cmd[0])
	{
		if (!ft_strncmp(process->cmd[0], "echo", ft_strlen("echo")))
			builtin_echo(process, fd);
		else if (!ft_strncmp(process->cmd[0], "cd", ft_strlen("cd")))
			builtin_cd(process, *env);
		else if (!ft_strncmp(process->cmd[0], "pwd", ft_strlen("pwd")))
			builtin_pwd(fd);
		else if (!ft_strncmp(process->cmd[0], "env", ft_strlen("env")))
			builtin_env(*env, fd);
		else if (!ft_strncmp(process->cmd[0], "export", ft_strlen("export")))
			builtin_export(process, *env, fd, e_info);
		else if (!ft_strncmp(process->cmd[0], "unset", ft_strlen("unset"))
			&& e_info.cmd_size == 1)
		{
			builtin_unset(process, env);
		}
		else if (!ft_strncmp(process->cmd[0], "exit", ft_strlen("exit")))
			builtin_exit(process, e_info);
	}
	return ;
}

int	is_builtin(t_process *process)
{
	int	len;

	if (process->cmd[0])
	{
		len = ft_strlen(process->cmd[0]);
		if (!ft_strncmp(process->cmd[0], "echo", ft_strlen("echo")) && len == 4)
			return (1);
		if (!ft_strncmp(process->cmd[0], "cd", ft_strlen("cd")) && len == 2)
			return (1);
		if (!ft_strncmp(process->cmd[0], "pwd", ft_strlen("pwd")) && len == 3)
			return (1);
		if (!ft_strncmp(process->cmd[0], "export", ft_strlen("export"))
			&& len == 6)
			return (1);
		if (!ft_strncmp(process->cmd[0], "unset", ft_strlen("unset"))
			&& len == 5)
			return (1);
		if (!ft_strncmp(process->cmd[0], "env", ft_strlen("env")) && len == 3)
			return (1);
		if (!ft_strncmp(process->cmd[0], "exit", ft_strlen("exit")) && len == 4)
			return (1);
	}
	return (0);
}
