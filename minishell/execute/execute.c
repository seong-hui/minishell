/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/11/02 21:50:29 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	fork_toexcute(t_process *process, t_env *env, t_excute e_info)
{
	e_info.execute_path = get_path(env);
	make_pipe(process, env, e_info);
	return (0);
}

void	no_fork_toexecute(t_process *process, t_env *env)
{
	fd_redirection(process, process->redir);
	check_builtins(process, env, process->outfile_fd);
}

void	unlink_file(t_redir *redir)
{
	while (redir)
	{
		if (redir->tmp)
			unlink(redir->tmp);
		redir = redir->next;
	}
}

void	process_start(t_process *process, t_env *env, char **envp)
{
	t_process	*head;
	t_redir		*head_redir;
	t_excute	e_info;

	head = process;
	head_redir = process->redir;
	check_heredoc(process);
	if (!head->cmd[0])
	{
		fd_redirection(process, process->redir);
		unlink_file(process->redir);
		return ;
	}
	if (!process)
		return ;
	e_info.cmd_size = ft_lstsize(process);
	e_info.envp = envp;
	if (e_info.cmd_size == 1 && is_builtin(head))
		no_fork_toexecute(head, env);
	else
		fork_toexcute(head, env, e_info);
}
