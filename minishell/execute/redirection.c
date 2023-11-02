/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:15:18 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/02 23:13:33 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	redir_input(t_process *process, t_redir *redir)
{
	process->infile_fd = open(redir->file, O_RDONLY);
	if (process->infile_fd == -1)
	{
		perror("Failed to open infile");
		exit(1);
	}
}

void	redir_heredoc(t_process *process, t_redir *redir)
{
	process->infile_fd = open(redir->tmp, O_RDONLY);
	if (process->infile_fd == -1)
	{
		perror("Failed to open infile");
		exit(1);
	}
	unlink(redir->tmp);
}

void	redir_output(t_process *process, t_redir *redir)
{
	process->outfile_fd = open(redir->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (process->outfile_fd == -1)
	{
		perror("Failed to open outfile");
		exit(1);
	}
}

void	redir_append(t_process *process, t_redir *redir)
{
	process->outfile_fd = open(redir->file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (process->outfile_fd == -1)
	{
		perror("Failed to open outfile");
		exit(1);
	}
}

void	fd_redirection(t_process *process, t_redir *redir)

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
		redir = redir->next;
	}
}
