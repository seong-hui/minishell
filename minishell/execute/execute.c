/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:32:17 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/06 21:11:53 by seonghmo         ###   ########.fr       */
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
			free (str[i]);
			i++;
		}
		free (str);
	}
}

// void	free_e_info(t_excute *e_info)
// {
// 	int			i;

// 	free_redir_list(e_info->redir);
// 	free(e_info->cmd_line);
// 	i = 0;
// 	while (process->cmd && process->cmd[i])
// 		free(process->cmd[i++]);
// 	free(process->cmd);
// 	free(process);
// }


void free_execute(t_excute exe_info)
{
	if (exe_info.execute_path)
		arr_free(exe_info.execute_path);
}

int	fork_toexcute(t_process *process, t_env *env, t_excute e_info)
{
	e_info.execute_path = get_path(env);
	make_pipe(process, env, e_info);
	free_execute(e_info);
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

char ** copy_envp(char **envp)
{
	int	i;
	char **tmp;
	char **start;

	i = 0;
	start = tmp;
	while(envp[i])
	{
		tmp[i] = ft_strdup(envp[i]);
		i++;
	}
	tmp = start;
	return (tmp);
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
