/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:15:18 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/31 17:33:46 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void fd_redirection(t_process *process, t_redir *redir)

{
	process->infile_fd = 0;
	process->outfile_fd = 1;
	while (redir)
	{
		if (redir->type == T_REDIR_INPUT) // infile이 있을 때
		{
			process->infile_fd = open(redir->file, O_RDONLY);
			if (process->infile_fd == -1)
			{
				perror("Failed to open infile");
				exit(1);
			}
		}
		else if (redir->type == T_REDIR_HEREDOC) // infile이 있을 때
		{
			process->infile_fd = open(redir->tmp, O_RDONLY);
			if (process->infile_fd == -1)
			{
				perror("Failed to open infile");
				exit(1);
			}
			unlink(redir->tmp);
		}
		else if (redir->type == T_REDIR_OUTPUT) // outfile이 있을 때
		{
			process->outfile_fd = open(redir->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (process->outfile_fd == -1)
			{
				perror("Failed to open outfile");
				exit(1);
			}
		}
		else if (redir->type == T_REDIR_APPEND) // APPEND 처리 따로 해야함
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