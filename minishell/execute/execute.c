/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:03:26 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/23 20:36:44 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

char	*get_cmd(char **path, char *cmd);


void fd_redirection(t_process *process, t_redir *redir)

{
	process->infile_fd = 0;
	process->outfile_fd = 1;
	while(redir)
	{
		if (redir->type == 2) //infile이 있을 때
		{
			process->infile_fd = open(redir->file, O_RDONLY);
		 	if (process->infile_fd == -1) {
            	perror("Failed to open infile");
            	exit(1);
        	}
		}
		else if (redir->type == 3) //outfile이 있을 때 
		{
			process->outfile_fd = open(redir->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		 	if (process->outfile_fd == -1) 
		 	{
            	perror("Failed to open outfile");
            	exit(1);
		 	}
		}
		else if (redir->type == 5) //APPEND 처리 따로 해야함
		{
			process->outfile_fd = open(redir->file, O_RDWR | O_CREAT | O_APPEND, 0644);
		 	if (process->outfile_fd == -1) 
		 	{
            	perror("Failed to open outfile");
            	exit(1);
		 	}
		}
		redir = redir->next;
	}
}

void first_child(t_process *process, int *cur_fd)
{
	close(cur_fd[0]);
	if (process->infile_fd > 0)
		dup2(process->infile_fd, STDIN_FILENO);
	if (process->outfile_fd > 1)
		dup2(process->outfile_fd, STDOUT_FILENO);
	else if (process->next)
		dup2(cur_fd[1], STDOUT_FILENO);
	close(cur_fd[1]);
	// if (execve(cmd, process->cmd, env) == -1)
	// 	 perror("execve");
}

void middle_child(t_process *process, int *prev_fd, int *cur_fd)
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
	// if (execve(cmd, process->cmd, env) == -1)
	// 	exit(1);
}

void last_child(t_process *process, int *prev_fd)
{
	close(prev_fd[1]);
	if (process->infile_fd > 0)
		dup2(process->infile_fd, STDIN_FILENO);
	else
		dup2(prev_fd[0], STDIN_FILENO);
	if (process->outfile_fd > 1)
		dup2(process->outfile_fd, STDOUT_FILENO);
	close(prev_fd[0]);
	// if (execve(cmd, process->cmd, env) == -1)
	// 	exit(1);
}

void	close_pipe(int i, int *prev_fd, int *cur_fd)
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
	while (i > 0)
	{
		waitpid(-1, 0, 0);
		i--;
	}
}

void	make_pipe(t_process *process, int cmd_size, char **execute_path, t_env *env)
{
	pid_t	pid;
	int		i;
	int prev_fd[2];
	int cur_fd[2];
	

	if (pipe(prev_fd) == -1)
		exit(1);
	i = 0;
	
	while (process)
	{
		fd_redirection(process, process->redir);
		
		//printf("%d %d %d\n", i, process->infile_fd, process->outfile_fd);
		
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
		//pipe(process->cur_fd);
		printf("%d %d | %d %d|\n", prev_fd[0], prev_fd[1], cur_fd[0], cur_fd[1]);
		
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
		{
			char *cmd = get_cmd(execute_path, process->cmd[0]);
			if (i == 0)
				first_child(process, cur_fd);
			else if (i == cmd_size - 1)
				last_child(process, prev_fd);
			else
				middle_child(process, prev_fd, cur_fd);
			if (is_builtin(process))
				check_biltins(process, env, 1);
			else
			{
				if (execve(cmd, process->cmd, execute_path) == -1)
		 			perror("execve");
				printf("[test]\n");
			}
		}
		//  if (i > 0)
        // {
        //     close(prev_fd[0]);
        //     close(prev_fd[1]);
        // }

		// close(prev_fd[0]);
		// close(prev_fd[1]);
			
			// close(process->cur_fd[0]);
			// close(process->cur_fd[1]);
			process = process->next;
			i++;
	}
	close_pipe(i, prev_fd, cur_fd);
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


char	**get_path(t_env *env)
{
	char	**path;

	path = NULL;
	while (env)
	{
		if (ft_strncmp("PATH", env->key, 4) == 0)
		{
			path = ft_split(env->value, ':');
			break ;
		}
		env = env->next;
	}
	return (path);
}


int fork_toExcute(t_process *process, t_env *env, int cmd_size)
{
	char **execute_path;
	execute_path = get_path(env);
	//check_heredoc(process);
	make_pipe(process, cmd_size, execute_path, env);
	return (0);
}

void no_fork_toExecute(t_process *process, t_env *env)
{

	check_biltins(process, env, 1);
}

int is_builtin(t_process *process)
{
	if (!ft_strncmp(process->cmd[0], "echo", ft_strlen("echo")))
		return (1);
	else if (!ft_strncmp(process->cmd[0], "cd", ft_strlen("cd")))
		return (1);
	else if (!ft_strncmp(process->cmd[0], "pwd", ft_strlen("pwd")))
		return (1);
	else if (!ft_strncmp(process->cmd[0], "export", ft_strlen("export")))
		return (1);
	else if (!ft_strncmp(process->cmd[0], "unset", ft_strlen("unset")))
	return (1);
	else if (!ft_strncmp(process->cmd[0], "env", ft_strlen("env")))
		return (1);
	else if (!ft_strncmp(process->cmd[0], "exit", ft_strlen("exit")))
		return (1);
	return (0);
}

void process_start(t_process **process, t_env *env)
{
	t_process *head = process;
    int process_len;
	if (!process)
		return;
    process_len = ft_lstsize(process);
	// printf("[%d]\n", process_len);
	
    if (process_len == 1 && is_builtin(head)) //process 1개 && builtin인 경우
	{
		no_fork_toExecute(head, env);
	}
	else // 그 외는 다 포크해서 실행하기
	{
		fork_toExcute(head, env, process_len);
	}
}