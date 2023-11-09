/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:20:12 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/09 15:16:45 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

static void	close_pipe(int *prev_fd, int *cur_fd, int pid)
{
	int	flag_printed;
	int	status;
	int	child;

	if (prev_fd)
	{
		close(prev_fd[0]);
		close(prev_fd[1]);
	}
	if (pid > 0)
	{
		if (cur_fd)
		{
			close(cur_fd[0]);
			close(cur_fd[1]);
		}
		flag_printed = 0;
		child = waitpid(-1, &status, 0);
		while (child > 0)
		{
			exit_code_handler(status, &flag_printed, pid, child);
			child = waitpid(-1, &status, 0);
		}
	}
}

void	exit_code_handler(int status, int *flag_printed, int pid, int child)
{
	int	signo;

	if (WIFSIGNALED(status))
	{
		signo = WTERMSIG(status);
		if ((*flag_printed) == 0)
		{
			if (signo == SIGINT)
				printf("^C\n");
			(*flag_printed) = 1;
		}
		if (child == pid)
			g_exit_code = 128 + signo;
	}
	else if (child == pid)
		g_exit_code = WEXITSTATUS(status);
}

void	handle_fd(int *prev_fd, int *cur_fd)
{
	close(prev_fd[0]);
	close(prev_fd[1]);
	prev_fd[0] = cur_fd[0];
	prev_fd[1] = cur_fd[1];
}

void	child_process(t_process *proc, t_env *env, t_excute info, int *cur_fd)
{
	proc->cmd_path = get_cmd(info.execute_path, proc->cmd[0]);
	if (info.i == info.cmd_size - 1)
	{
		if (info.cmd_size == 1)
			info.prev_fd[0] = dup(STDIN_FILENO);
		last_child(proc, env, info);
	}
	else if (info.i == 0)
		first_child(proc, cur_fd, env, info);
	else
		middle_child(proc, cur_fd, env, info);
}

void	make_pipe(t_process *process, t_env *env, t_excute exe_info)
{
	pid_t	pid;
	int		cur_fd[2];
	int		flag;

	if (pipe(exe_info.prev_fd) == -1)
		exit_and_setcode();
	pid = 0;
	handle_signal();
	while (exe_info.i < exe_info.cmd_size)
	{
		flag = fd_redirection(process, process->redir);
		if (flag)
		{
			if (exe_info.i > 0 && cur_fd[0] > 0 && cur_fd[1] > 1)
				handle_fd(exe_info.prev_fd, cur_fd);
			if (pipe(cur_fd) == -1)
				exit_and_setcode();
			pid = fork();
			if (pid < 0)
				exit_and_setcode();
			if (pid == 0)
				child_process(process, env, exe_info, cur_fd);
			if (process->infile_fd != STDIN_FILENO)
				close(process->infile_fd);
			if (process->outfile_fd != STDOUT_FILENO)
				close(process->outfile_fd);
		}
		process = process->next;
		exe_info.i += 1;
	}
	close_pipe(exe_info.prev_fd, cur_fd, pid);
}
