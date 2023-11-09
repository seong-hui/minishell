/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:03:14 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/09 16:31:11 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void	unset_env(t_env *env, t_process *process, int i, t_env *start)
{
	if (!ft_strcmp(process->cmd[i], "_"))
	{
		g_exit_code = 0;
		return ;
	}
	while (env)
	{
		if (ft_strcmp(env->key, process->cmd[i]) == 0)
		{
			delete_env(&start, env->key);
			break ;
		}
		else
			env = env->next;
	}
}

void	builtin_unset(t_process *process, t_env *env, int fd)
{
	int		i;
	t_env	*start;

	start = env;
	i = 1;
	while (process->cmd[i])
	{
		if ((process->cmd[i][0] == '_')
			|| ft_isalpha(process->cmd[i][0]))
		{
			env = start;
			unset_env(env, process, i, start);
		}
		else
			print_unset_error(process->cmd[i]);
		i++;
	}
	return ;
}
