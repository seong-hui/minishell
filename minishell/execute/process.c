/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:23:48 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/14 22:15:36 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"
#include <sys/stat.h>

void	first_child(t_process *proc, int *cur_fd, t_env **env, t_excute e_info)
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

void	middle_child(t_process *proc, int *cur_fd, t_env **env, t_excute e_info)
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

void	evecve_error(char *valid_cmd, char *simple_cmd)
{
	struct stat	st;

	stat(simple_cmd, &st);
	if (S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(simple_cmd, 2);
		ft_putendl_fd(": is a directory", 126);
		g_exit_code = 126;
	}
	else
	{
		if (access(valid_cmd, F_OK) < 0)
			printf("test1\n");
		else if (access(valid_cmd, X_OK) < 0)
			printf("test2\n");
		else
			exit(0);
	}
}

void	last_child(t_process *process, t_env **env, t_excute e_info)
{
	close(e_info.prev_fd[1]);
	if (process->infile_fd > 0)
		dup2(process->infile_fd, STDIN_FILENO);
	else
		dup2(e_info.prev_fd[0], STDIN_FILENO);
	if (process->outfile_fd > 1)
		dup2(process->outfile_fd, STDOUT_FILENO);
	close(e_info.prev_fd[0]);
	if (is_builtin(process))
	{
		check_builtins(process, env, process->outfile_fd, e_info);
		exit(0);
	}
	else
	{
		if (execve(process->cmd_path, process->cmd, e_info.envp) == -1)
		{
			evecve_error(process->cmd_path,process->cmd[0] );
			// print_command_error(process->cmd[0]);
		}
			
	}
}
