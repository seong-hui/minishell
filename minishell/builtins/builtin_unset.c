/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:03:14 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/14 19:51:40 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

static void	unset_env(t_env **env, t_process *process, int i)
{
	t_env	*start;

	start = *env;
	if (!ft_strcmp(process->cmd[i], "_"))
	{
		g_exit_code = 0;
		return ;
	}
	while (start)
	{
		if (ft_strcmp(start->key, process->cmd[i]) == 0)
		{
			delete_env(env, start->key);
			break ;
		}
		else
			start = start->next;
	}
}

void	builtin_unset(t_process *process, t_env **env)
{
	int		i;

	i = 1;
	while (process->cmd[i])
	{
		if (check_vaild_key(process->cmd[i]) || (process->cmd[i][0] == '_'
			&& (!process->cmd[i][1])))
			unset_env(env, process, i);
		else
			print_unset_error(process->cmd[i]);
		i++;
	}
	return ;
}
