/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:32:17 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/13 20:23:45 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	arr_free(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

static int	fork_toexcute(t_process *process, t_env *env, t_excute e_info)
{
	e_info.execute_path = get_path(env);
	e_info.i = -1;
	make_pipe(process, env, e_info);
	while (process)
	{
		unlink_file(process->redir);
		process = process->next;
	}
	if (e_info.execute_path)
		arr_free(e_info.execute_path);
	return (0);
}

static void	no_fork_toexecute(t_process *process, t_env *env, t_excute e_info)
{
	fd_redirection(process, process->redir);
	check_builtins(process, env, process->outfile_fd, e_info);
}

static int	check_rider(t_process *process)
{
	int			count;
	t_redir		*head_redir;
	t_process	*head;

	head_redir = process->redir;
	head = process;
	while (head)
	{
		count = 0;
		while (head_redir)
		{
			if (head_redir->type == T_REDIR_HEREDOC)
				count++;
			head_redir = head_redir->next;
		}
		if (count > 16)
		{
			ft_putendl_fd("minishell: maximum here-document count exceeded", 2);
			return (0);
		}
		head = head->next;
	}
	return (1);
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
	if (check_rider(process))
		check_heredoc(process, env);
	if (!head->cmd[0] || g_exit_code == 1)
		unlink_file(process->redir);
	if (g_exit_code != 1)
	{
		e_info.envp = envp;
		if (e_info.cmd_size == 1 && is_builtin(head))
			no_fork_toexecute(head, env, e_info);
		else
			fork_toexcute(head, env, e_info);
	}
}
