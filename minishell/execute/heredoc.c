/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:11:51 by moonseonghu       #+#    #+#             */
/*   Updated: 2023/11/09 17:49:50 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	execute_heredoc(t_process *process, t_redir *redir, t_env *env)
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
		buffer = replace_str(buffer, &env);
		ft_putstr_fd(buffer, process->infile_fd);
		ft_putstr_fd("\n", process->infile_fd);
		free(buffer);
	}
}

char	*make_tmp_heredoc(void)
{
	char	*tmp_heredoc;
	int		i;
	char	*i_str;
	int		fd;

	i = 0;
	while (1)
	{
		i_str = ft_itoa(i);
		tmp_heredoc = ft_strjoin("tmp_file", i_str);
		free(i_str);
		fd = open(tmp_heredoc, O_RDONLY);
		if (fd == -1)
			return (tmp_heredoc);
		close(fd);
		free(tmp_heredoc);
		i++;
	}
	return (NULL);
}

void	handle_heredoc(t_redir *redir, t_process *proc, t_here *he, t_env *env)
{
	redir->tmp = make_tmp_heredoc();
	he->pid = fork();
	if (he->pid < 0)
		exit(1);
	he->i += 1;
	signal(SIGTERM, heredoc_signal);
	signal(SIGINT, heredoc_signal);
	if (he->pid == 0)
	{
		proc->infile_fd = open(redir->tmp, O_RDWR | O_CREAT | O_TRUNC, 0644);
		free(redir->tmp);
		execute_heredoc(proc, redir, env);
		close(proc->infile_fd);
		exit(0);
	}
	else
		signal(SIGINT, SIG_IGN);
}

void	check_heredoc(t_process *process, t_env *env)
{
	t_redir	*tmp_redir;
	int		exit_code;
	t_here	here;

	here.i = 0;
	g_exit_code = 0;
	while (process)
	{
		tmp_redir = process->redir;
		while (tmp_redir)
		{
			if (tmp_redir->type == T_REDIR_HEREDOC)
				handle_heredoc(tmp_redir, process, &here, env);
			waitpid(here.pid, &exit_code, 0);
			if (child_exit_status(exit_code))
				break ;
			tmp_redir = tmp_redir->next;
		}
		if (g_exit_code != 0)
			break ;
		process = process->next;
	}
	wait_child(here.i, exit_code);
	detect_signal();
}
