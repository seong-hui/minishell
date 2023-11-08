/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:23:48 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/08 20:19:06 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void first_child(t_process *proc, int *cur_fd, t_env *env, t_excute e_info)
{
	close(cur_fd[0]);
	if (proc->infile_fd > 0)
		dup2(proc->infile_fd, STDIN_FILENO);
	if (proc->outfile_fd > 1)
		dup2(proc->outfile_fd, STDOUT_FILENO);
	else
		dup2(cur_fd[1], STDOUT_FILENO);
	if (is_builtin(proc))
	{
		check_builtins(proc, env, proc->outfile_fd, e_info);
		close(cur_fd[1]);
		exit(0);
	}
	else
	{
		close(cur_fd[1]);
		if (execve(proc->cmd_path, proc->cmd, e_info.envp) == -1)
			print_command_error(proc->cmd[0]);
	}
}

void middle_child(t_process *proc, int *cur_fd, t_env *env, t_excute e_info)
{
	close(cur_fd[0]);
	close(e_info.prev_fd[1]);
	if (proc->infile_fd > 0)
		dup2(proc->infile_fd, STDIN_FILENO);
	else
		dup2(e_info.prev_fd[0], STDIN_FILENO);
	if (proc->outfile_fd > 1)
		dup2(proc->outfile_fd, STDOUT_FILENO);
	else
		dup2(cur_fd[1], STDOUT_FILENO);
	close(e_info.prev_fd[0]);
	if (is_builtin(proc))
	{
		check_builtins(proc, env, proc->outfile_fd, e_info);
		close(cur_fd[1]);
		exit(0);
	}
	else
	{
		close(cur_fd[1]);
		if (execve(proc->cmd_path, proc->cmd, e_info.envp) == -1)
			print_command_error(proc->cmd[0]);
	}
}

void last_child(t_process *process, t_env *env, t_excute e_info)
{
	close(e_info.prev_fd[1]);
	if (process->infile_fd > 0)
	{
		dup2(process->infile_fd, STDIN_FILENO);
		// close(process->infile_fd);
	}
	else
		dup2(e_info.prev_fd[0], STDIN_FILENO);
	if (process->outfile_fd > 1)
	{
		dup2(process->outfile_fd, STDOUT_FILENO);
	}
	close(e_info.prev_fd[0]);
	if (is_builtin(process))
	{
		check_builtins(process, env, process->outfile_fd, e_info);
		// close(process->outfile_fd);
		exit(0);
	}
	else
	{
		if (execve(process->cmd_path, process->cmd, e_info.envp) == -1)
			print_command_error(process->cmd[0]);
	}
}
