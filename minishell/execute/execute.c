/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:03:26 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/17 21:02:19 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

char	*get_cmd(char **path, char *cmd);


void fd_redirection(t_process *process)
{
	printf("%d\n", process->redir->type);
	
	if (process->redir->type == 2) //infile이 있을 때
	{
		process->infile_fd = open(process->redir->file, O_RDONLY);
		 if (process->infile_fd == -1) {
            perror("Failed to open infile");
            exit(1);
        }
	}
	if (process->redir->type == 3) //outfile이 있을 때
	{
		process->outfile_fd = open(process->redir->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		 if (process->outfile_fd == -1) {
            perror("Failed to open outfile");
            exit(1);
		 }
	}
	printf("test1\n");
}

void first_child(t_process *process, char **envp, char *cmd, int *prev_fd, int *cur_fd)
{
	close(cur_fd[0]);
	if (process->infile_fd > 0)
		dup2(process->infile_fd, STDIN_FILENO);
	if (process->outfile_fd > 1)
		dup2(process->outfile_fd, STDOUT_FILENO);
	else
		dup2(cur_fd[1], STDOUT_FILENO);
	close(cur_fd[1]);
	if (execve(cmd, process->cmd, envp) == -1)
		 perror("execve");
}

void middle_child(t_process *process, char **envp, char *cmd, int *prev_fd, int *cur_fd)
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
	close(cur_fd[1]);
	close(prev_fd[0]);
	if (execve(cmd, process->cmd, envp) == -1)
		exit(1);
}

void last_child(t_process *process, char **envp, char *cmd, int *prev_fd, int *cur_fd)
{
	close(prev_fd[1]);
	if (process->infile_fd > 0)
		dup2(process->infile_fd, STDIN_FILENO);
	else
		dup2(prev_fd[0], STDIN_FILENO);
	if (process->outfile_fd > 1)
		dup2(process->outfile_fd, STDOUT_FILENO);
	close(prev_fd[0]);
	if (execve(cmd, process->cmd, envp) == -1)
		exit(1);
}



void	close_fife(int i, int *prev_fd, int *cur_fd)
{
	close(prev_fd[0]);
	close(prev_fd[1]);
	close(cur_fd[0]);
	close(cur_fd[1]);
	printf("%d\n", i);
	while (i > 0)
	{
		waitpid(-1, 0, 0);
		i--;
		printf("%d\n", i);
	}
	
}

void	make_pipe(t_process *process, int cmd_size, char **envp)
{
	pid_t	pid;
	int		i;
	int prev_fd[2];
	int cur_fd[2];

	if (pipe(prev_fd) == -1)
		exit(1);
	i = 0;
	pipe(cur_fd);
	
	while (i < cmd_size)
	{
		process->infile_fd = 0;
		process->outfile_fd = 1;
		
		fd_redirection(process);
		printf("test\n");
		//printf("%d %d %d\n", i, process->infile_fd, process->outfile_fd);
		printf("%d %d | %d %d|\n", prev_fd[0], prev_fd[1], cur_fd[0], cur_fd[1]);
		prev_fd[0] = cur_fd[0];
		prev_fd[1] = cur_fd[1];
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
		{
			char *cmd = get_cmd(envp, process->cmd[0]);
			if (i == 0)
				first_child(process, envp, cmd, prev_fd, cur_fd);
			else if (i == cmd_size - 1)
				last_child(process, envp, cmd, prev_fd, cur_fd);
			else
				middle_child(process, envp, cmd, prev_fd, cur_fd);
		}
			process = process->next;
			i++;
	}
	close_fife(i, prev_fd, cur_fd);
	printf("test");
}

int	ft_lstsize(t_process *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		printf("%s\n", lst->cmd_line);
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
	
	make_pipe(process, cmd_size, envp);
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
	printf("[%d]\n", process_len);
    if (process_len == 1 && is_builtin(process)) //process 1개 && builtin인 경우
	{
		no_fork_toExecute(process);
	}
	else // 그 외는 다 포크해새 실행하기
	{
		fork_toExcute(process, envp, process_len);
	}
}