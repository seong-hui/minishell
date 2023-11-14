/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:15:18 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/14 14:56:32 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	redir_input(t_process *process, t_redir *redir)
{
	if (process->infile_fd != STDIN_FILENO)
		close(process->infile_fd);
	process->infile_fd = open(redir->file, O_RDONLY);
	if (process->infile_fd == -1)
	{
		g_exit_code = 1;
		ft_putstr_fd("minishell: ", 2);
		perror(redir->file);
	}
}

void	redir_heredoc(t_process *process, t_redir *redir)
{
	if (process->infile_fd != STDIN_FILENO)
		close(process->infile_fd);
	process->infile_fd = open(redir->tmp, O_RDONLY);
	if (process->infile_fd == -1)
	{
		g_exit_code = 1;
		ft_putstr_fd("minishell: ", 2);
		perror(redir->file);
	}
	unlink(redir->tmp);
}

void	redir_output(t_process *process, t_redir *redir)
{
	if (process->outfile_fd != STDOUT_FILENO)
		close(process->outfile_fd);
	process->outfile_fd = open(redir->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (process->outfile_fd == -1)
	{
		g_exit_code = 1;
		ft_putstr_fd("minishell: ", 2);
		perror(redir->file);
	}
}

void	redir_append(t_process *process, t_redir *redir)
{
	if (process->outfile_fd != STDOUT_FILENO)
		close(process->outfile_fd);
	process->outfile_fd = open(redir->file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (process->outfile_fd == -1)
	{
		g_exit_code = 1;
		ft_putstr_fd("minishell: ", 2);
		perror(redir->file);
	}
}

int	fd_redirection(t_process *process, t_redir *redir)
{
	process->infile_fd = 0;
	process->outfile_fd = 1;
	while (redir)
	{
		if (redir->type == T_REDIR_INPUT)
			redir_input(process, redir);
		else if (redir->type == T_REDIR_HEREDOC && process->cmd[0])
			redir_heredoc(process, redir);
		else if (redir->type == T_REDIR_OUTPUT)
			redir_output(process, redir);
		else if (redir->type == T_REDIR_APPEND)
			redir_append(process, redir);
		if (process->infile_fd < 0 || process->outfile_fd < 0)
		{
			if (process->infile_fd != STDIN_FILENO)
				close(process->infile_fd);
			if (process->outfile_fd != STDOUT_FILENO)
				close(process->outfile_fd);
			unlink_file(redir);
			g_exit_code = 1;
			return (0);
		}
		redir = redir->next;
	}
	return (1);
}
