/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:03:26 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/16 06:05:12 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void fd_redirection(t_process *process)
{
	printf("test\n");
	if (process->redir->type == 2) //infile이 있을 때
	{
		process->infile_fd = open(process->redir->file, O_RDONLY);
		 if (process->infile_fd == -1) {
            perror("Failed to open infile");
            exit(1);
        }
		 if (dup2(process->infile_fd, STDIN_FILENO) == -1)
            exit(1);
        close(process->infile_fd);
	}
	if (process->redir->type == 3) //outfile이 있을 때
	{
		process->outfile_fd = open(process->redir->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		 if (process->outfile_fd == -1) {
            perror("Failed to open outfile");
            exit(1);
        }
		 if (dup2(process->outfile_fd, STDOUT_FILENO) == -1)
            exit(1);
        close(process->outfile_fd);
	}
}

void first_child(t_process *process, char **envp, char *cmd)
{
	
	 close(process->pipefd[0]);
    if (dup2(process->pipefd[1], STDOUT_FILENO) == -1)
	{
        perror("dup2");
	}
	//fd_redirection(process);
	if (execve(cmd, process->cmd, envp) == -1)
		exit(1);
	close(process->pipefd[1]);
	printf("test\n");
}

void last_child(t_process *process, char **envp, char *cmd)
{
	close(process->pipefd[1]);
	if (dup2(process->pipefd[0], STDIN_FILENO) == -1) 
		exit(1);
	close(process->pipefd[0]);
	//fd_redirection(process);
	if (execve(cmd, process->cmd, envp) == -1)
		exit(1);
}

void middle_child(t_process *process, char **envp, char *cmd)
{
    if (dup2(process->pipefd[1], STDIN_FILENO) == -1) // 중간 프로세스에서 입력을 이전 파이프의 쓰는 부분으로 연결
        exit(1);
	if (dup2(process->pipefd[0], STDOUT_FILENO) == -1)
        exit(1);
    close(process->pipefd[0]);
	close(process->pipefd[1]);
	//fd_redirection(process);
	if (execve(cmd, process->cmd, envp) == -1)
		exit(1);
}

void	close_fife(t_process *process, int i)
{
	close(process->pipefd[0]);
	close(process->pipefd[1]);
	while (i > 0)
	{
		waitpid(-1, 0, 0);
		i--;
	}
}

void	make_pipe(t_process *process, int cmd_size, char **envp, char *cmd)
{
	pid_t	pid;
	int		i;
	int pipefd[2];

	if (pipe(process->pipefd) == -1)
		exit(1);
	i = 0;
	while (i < cmd_size)
	{
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
		{
			if (i == 0)
				first_child(process, envp, cmd);
			else if (i == cmd_size - 1)
				last_child(process, envp, cmd);
			else
				middle_child(process, envp, cmd);
		}
			process = process->next;
			i++;
	}
	close_fife(process, i);
}

int	ft_lstsize(t_process *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

char	*get_cmd(char **path, char *cmd)
{
	int		i;
	char	*tmp_cmd;
	int		fd;
	char	*tmp;

	i = 0;
	fd = access(cmd, X_OK);
	if (fd != -1)
		return (ft_strdup(cmd));
	tmp_cmd = ft_strjoin("/", cmd);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], tmp_cmd);
		fd = access(tmp, X_OK);
		if (fd != -1)
		{
			free(tmp_cmd);
			return (tmp);
		}
		close(fd);
		free(tmp);
		i++;
	}
	free(tmp_cmd);
	return (0);
}

int fork_toExcute(t_process *process, char **envp, int cmd_size)
{
	char *cmd;

	cmd = get_cmd(envp, process->cmd[0]);
	printf("%s\n", cmd);
	make_pipe(process, cmd_size, envp, cmd);
	return (0);
}

void no_fork_toExecute(t_process *process)
{
	
}

int is_builtin(t_process *process)
{
	return (0);
}

void process_start(t_process *process, char **envp)
{
    int process_len;

    process_len = ft_lstsize(process);
    if (process_len == 1 && is_builtin(process)) //process 1개 && builtin인 경우
	{
		no_fork_toExecute(process);
	}
	else // 그 외는 다 포크해새 실행하기
	{
		fork_toExcute(process, envp, process_len);
	}
}