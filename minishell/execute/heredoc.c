/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:11:51 by moonseonghu       #+#    #+#             */
/*   Updated: 2023/10/31 21:03:40 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	execute_heredoc(t_process *process, t_redir *redir)
{
	char	*buffer;

	while (1)
	{
		buffer = readline("> ");
		if (buffer == NULL)
			break ;
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

void	check_heredoc(t_process *process)
{
	t_redir	*tmp_redir;
	int		i;
	pid_t	pid;

	i = 0;
	while (process)
	{
		tmp_redir = process->redir;
		while (tmp_redir)
		{
			if (tmp_redir->type == T_REDIR_HEREDOC)
			{
				// pid = fork();
				// if (pid < 0)
				// 	exit(1);
					tmp_redir->tmp = make_tmp_heredoc();
					process->infile_fd = open(tmp_redir->tmp, O_RDWR | O_CREAT | O_TRUNC, 0644);
					execute_heredoc(process, tmp_redir);
					close(process->infile_fd);
				
			}
			tmp_redir = tmp_redir->next;
		}
		process = process->next;
	}
}
