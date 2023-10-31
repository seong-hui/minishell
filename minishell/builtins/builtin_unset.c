/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:03:14 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/31 14:34:30 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void	builtin_unset(t_process *process, t_env *env, int fd)
{
	int		i;
	t_env	*start;

	start = env;
	i = 1;
	while (process->cmd[i])
	{
		if ((process->cmd[i][0] == '_' && process->cmd[i][1])
			|| ft_isalpha(process->cmd[i][0]))
		{
			env = start;
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
		else
		{
			ft_putstr_fd(process->cmd[i], fd);
			ft_putstr_fd(": not a valid identifier\n", fd);
		}
		i++;
	}
	return ;
}
