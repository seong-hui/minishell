/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/31 20:54:10 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	fork_toexcute(t_process *process, t_env *env, int cmd_size, char **envp)
{
	char	**execute_path;

	execute_path = get_path(env);
	make_pipe(process, cmd_size, execute_path, env, envp);
	return (0);
}

void	no_fork_toexecute(t_process *process, t_env *env)
{
	fd_redirection(process, process->redir);
	check_builtins(process, env, process->outfile_fd);
}


void	process_start(t_process *process, t_env *env, char **envp)
{
	t_process	*head;
	t_redir		*head_redir;
	int			process_len;

	head = process;
	head_redir = process->redir;
	check_heredoc(process);
	if (!process->cmd[0])
	{
		fd_redirection(process, process->redir);
		return ;
	}
	if (!process)
		return ;
	process_len = ft_lstsize(process);
	if (process_len == 1 && is_builtin(head))
		no_fork_toexecute(head, env);
	else
		fork_toexcute(head, env, process_len, envp);
}
