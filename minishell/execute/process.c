/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:23:48 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/31 21:48:34 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	first_child(t_process *process, int *cur_fd, t_env *env, char *cmd, char **envp)
{
	close(cur_fd[0]);
	if (process->infile_fd > 0)
		dup2(process->infile_fd, STDIN_FILENO);
	if (process->outfile_fd > 1)
		dup2(process->outfile_fd, STDOUT_FILENO);
	else
		dup2(cur_fd[1], STDOUT_FILENO);
	if (is_builtin(process))
	{
		check_builtins(process, env, cur_fd[1]);
		close(cur_fd[1]);
		exit(0);
	}
	else
	{
		close(cur_fd[1]);
		if (execve(cmd, process->cmd, envp) == -1)
			print_command_error(process->cmd[0]);
	}
}

void	middle_child(t_process *process, int *prev_fd, int *cur_fd, t_env *env, char *cmd, char **envp)
{
	close(cur_fd[0]);
	close(prev_fd[1]);
	if (process->infile_fd > 0)
		dup2(process->infile_fd, STDIN_FILENO);
	else
		dup2(prev_fd[0], STDIN_FILENO);
	if (process->outfile_fd > 1)
		dup2(process->outfile_fd, STDOUT_FILENO);
	else
		dup2(cur_fd[1], STDOUT_FILENO);
	close(prev_fd[0]);
	if (is_builtin(process))
	{
		check_builtins(process, env, cur_fd[1]);
		close(cur_fd[1]);
		exit(0);
	}
	else
	{
		close(cur_fd[1]);
		if (execve(cmd, process->cmd, envp) == -1)
			print_command_error(process->cmd[0]);
	}
}

void	last_child(t_process *process, int *prev_fd, t_env *env, char *cmd, char **envp)
{
	close(prev_fd[1]);
	if (process->infile_fd > 0)
	{
		dup2(process->infile_fd, STDIN_FILENO);
		close(process->infile_fd);
	}
	else
		dup2(prev_fd[0], STDIN_FILENO);
	if (process->outfile_fd > 1)
	{
		dup2(process->outfile_fd, STDOUT_FILENO);
		close(process->outfile_fd);
	}
	close(prev_fd[0]);
	if (is_builtin(process))
	{
		check_builtins(process, env, process->outfile_fd);
		exit(0);
	}
	else
	{
		if (execve(cmd, process->cmd, envp) == -1)
			print_command_error(process->cmd[0]);
	}
}
