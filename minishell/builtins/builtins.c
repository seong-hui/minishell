/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:22:14 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/24 16:17:33 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void	check_builtins(t_process *process, t_env *env, int fd)
{
	//printf("[%s]\n", process->cmd[0]);
	if (!ft_strncmp(process->cmd[0], "echo", ft_strlen("echo")))
		builtin_echo(process, fd);
	else if (!ft_strncmp(process->cmd[0], "cd", ft_strlen("cd")))
		builtin_cd(process);
	else if (!ft_strncmp(process->cmd[0], "pwd", ft_strlen("pwd")))
		builtin_pwd();
	// else if (!ft_strncmp(process->cmd[0], "export", ft_strlen("export")))
	// 	builtin_export(process, env);
	// else if (!ft_strncmp(token[0], "unset", ft_strlen("unset")))
	// 	builtin_unset(token);
	else if (!ft_strncmp(process->cmd[0], "env", ft_strlen("env")))
		builtin_env(process, env, fd);
	// else if (!ft_strncmp(token[0], "exit", ft_strlen("exit")))
		// builtin_exit(token);
		return;
}

