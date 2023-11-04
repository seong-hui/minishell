/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/11/04 15:24:41 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	fork_toexcute(t_process *process, t_env *env, t_excute e_info)
{
	e_info.execute_path = get_path(env);
	make_pipe(process, env, e_info);
	return (0);
}

void	no_fork_toexecute(t_process *process, t_env *env, t_excute e_info)
{
	fd_redirection(process, process->redir);
	check_builtins(process, env, process->outfile_fd, e_info);
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
	if (!process)
		return ;
	e_info.cmd_size = ft_lstsize(process);
	check_heredoc(process);
	if (!head->cmd[0])
	{
		fd_redirection(process, process->redir);
		unlink_file(process->redir);
		return ;
	}
	e_info.envp = envp;
	if (e_info.cmd_size == 1 && is_builtin(head))
		no_fork_toexecute(head, env, e_info);
	else
		fork_toexcute(head, env, e_info);
}
