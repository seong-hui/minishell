/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/26 19:39:36 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void check_builtins(t_process *process, t_env *env, int fd, int is_single)
{
	if (!ft_strncmp(process->cmd[0], "echo", ft_strlen("echo")))
		builtin_echo(process, fd);
	else if (!ft_strncmp(process->cmd[0], "cd", ft_strlen("cd")))
		builtin_cd(process);
	else if (!ft_strncmp(process->cmd[0], "pwd", ft_strlen("pwd")))
		builtin_pwd();
	else if (!ft_strncmp(process->cmd[0], "env", ft_strlen("env")))
		builtin_env(process, env, fd);
	else if (!ft_strncmp(process->cmd[0], "export", ft_strlen("export")))
		builtin_export(process, env, fd);
	else if (!ft_strncmp(process->cmd[0], "unset", ft_strlen("unset")))
		builtin_unset(process, env, fd);
	else if (!ft_strncmp(process->cmd[0], "exit", ft_strlen("exit")))
		builtin_exit(process);
	return;
}
