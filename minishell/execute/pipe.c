/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:20:12 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/31 21:41:46 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

static void	close_pipe(int i, int *prev_fd, int *cur_fd, int pid)
{
	if (prev_fd)
	{
		close(prev_fd[0]);
		close(prev_fd[1]);
	}

	if (cur_fd)
	{
		close(cur_fd[0]);
		close(cur_fd[1]);
	}

	int	flag_printed;
	int	status;
	int	child;

	flag_printed = 0;
	child = waitpid(-1, &status, 0);
	while (child > 0)
	{
		exit_code_handler(status, &flag_printed, pid, child);
		child = waitpid(-1, &status, 0);
	}

	// while (i > 0)
	// {
	// 	waitpid(-1, 0, 0);
	// 	i--;
	// }
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


void	make_pipe(t_process *process, int cmd_size, char **execute_path, t_env *env, char **envp)
{
	pid_t	pid;
	int		i;
	int		prev_fd[2];
	int		cur_fd[2];
	char	*cmd;

	if (pipe(prev_fd) == -1)
		exit(1);
	prev_fd[0] = dup(STDIN_FILENO);
	i = 0;
	while (i < cmd_size)
	{
		fd_redirection(process, process->redir);
		if (i > 0)
		{
			close(prev_fd[0]);
			close(prev_fd[1]);
			prev_fd[0] = cur_fd[0];
			prev_fd[1] = cur_fd[1];
		}
		if (pipe(cur_fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0 && process->cmd[0])
		{
			cmd = get_cmd(execute_path, process->cmd[0]);
			if (i == cmd_size - 1)
				last_child(process, prev_fd, env, cmd, envp);
			else if (i == 0)
				first_child(process, cur_fd, env, cmd, envp);
			else
				middle_child(process, prev_fd, cur_fd, env, cmd, envp);
		}
		process = process->next;
		i++;
	}
	close_pipe(i, prev_fd, cur_fd, pid);
	//wait_process(pid);
}

