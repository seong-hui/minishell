/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:11:51 by moonseonghu       #+#    #+#             */
/*   Updated: 2023/10/31 23:43:57 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

#include <signal.h>

void	execute_heredoc(t_process *process, t_redir *redir)
{
	char	*buffer;
	

	while (1)
	{
		buffer = readline("> ");
		if (buffer == NULL)
		{
			break ;
		}
		if (!ft_strcmp(buffer, redir->file))
		{
			free(buffer);
			break ;
		}
		ft_putstr_fd(buffer, process->infile_fd);
		ft_putstr_fd("\n", process->infile_fd);
		free(buffer);
	}
}

char	*make_tmp_heredoc(void)
{
	char	*tmp_heredoc;
	int		i;

	i = 0;
	while (1)
	{
		tmp_heredoc = ft_strdup(ft_strjoin("tmp_file", ft_itoa(i)));
		if (open(tmp_heredoc, O_RDONLY) == -1)
			return (tmp_heredoc);
		i++;
	}
	return (NULL);
}

void wait_pid(int pid)
{
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
}

void	check_heredoc(t_process *process)
{
	t_redir	*tmp_redir;
	int		i;
	pid_t	pid;
	int		exit_code;


	i = 0;
	
	while (process)
	{
		tmp_redir = process->redir;
		while (tmp_redir)
		{
			if (tmp_redir->type == T_REDIR_HEREDOC)
			{
				pid = fork();
				if (pid < 0)
					exit(1);
				i++;
				signal(SIGINT, heredoc_signal);
				if (pid == 0)
				{
					tmp_redir->tmp = make_tmp_heredoc();
					process->infile_fd = open(tmp_redir->tmp, O_RDWR | O_CREAT | O_TRUNC, 0644);
					execute_heredoc(process, tmp_redir);
					close(process->infile_fd);
					exit(0);
				}
				else
					signal(SIGINT, SIG_IGN);
			}
				waitpid(pid, &exit_code, 0);
				if (WIFEXITED(exit_code))
				{
					if (exit_code != 0)
					{
						g_exit_code = exit_code;
						break ;
					}
				}
			tmp_redir = tmp_redir->next;
		}
		if (g_exit_code != 0)
			break ;
		process = process->next;
	}
	while (i > 0)
	{
		wait(&exit_code);
		i--;
	}
}
