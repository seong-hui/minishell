/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:11:51 by moonseonghu       #+#    #+#             */
/*   Updated: 2023/11/06 21:08:20 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"


void	execute_heredoc(t_process *process, t_redir *redir)
{
	char	*buffer;

	buffer = NULL;
	while (1)
	{
		buffer = readline("> ");
		if (buffer == NULL)
		{
			g_exit_code = 0;
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

void	handle_heredoc(t_redir	*redir, t_process *proc, pid_t *pid, int *i)
{
	redir->tmp = make_tmp_heredoc();
	(*pid) = fork();
	if ((*pid) < 0)
		exit(1);
	(*i)++;
	signal(SIGTERM, heredoc_signal);
	signal(SIGINT, heredoc_signal);
	if ((*pid) == 0)
	{
		proc->infile_fd = open(redir->tmp, O_RDWR | O_CREAT | O_TRUNC, 0644);
		execute_heredoc(proc, redir);
		close(proc->infile_fd);
		exit(0);
	}
	else
		signal(SIGINT, SIG_IGN);
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
				handle_heredoc(tmp_redir, process, &pid, &i);
			waitpid(pid, &exit_code, 0);
			if (child_exit_status(exit_code))
				break ;
			tmp_redir = tmp_redir->next;
		}
		if (g_exit_code != 0)
			break ;
		process = process->next;
	}
	wait_child(i, exit_code);
	detect_signal();
}
