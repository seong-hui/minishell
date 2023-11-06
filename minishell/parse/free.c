/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:48:25 by jooypark          #+#    #+#             */
/*   Updated: 2023/11/06 21:32:07 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	free_redir_list(t_redir *redir)
{
	t_redir	*next;

	while (redir)
	{
		free(redir->file);
		free(redir->tmp);
		next = redir->next;
		redir->next = NULL;
		free(redir);
		redir = next;
	}
}

void	free_process(t_process *process)
{
	int			i;

	free_redir_list(process->redir);
	free(process->cmd_line);
	free(process->cmd_path);
	i = 0;
	while (process->cmd && process->cmd[i])
		free(process->cmd[i++]);
	free(process->cmd);
	free(process);
}

void	free_process_list(t_process **process)
{
	t_process	*cur;
	t_process	*next;

	cur = *process;
	while (cur)
	{
		next = cur->next;
		cur->next = NULL;
		free_process(cur);
		cur = next;
	}
}

void	free_env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void	free_env_list(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		env->next = NULL;
		free_env(env);
		env = next;
	}
}
