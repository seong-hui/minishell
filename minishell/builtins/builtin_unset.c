/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:03:14 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/24 23:08:52 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void builtin_unset(t_process *process, t_env *env, int fd)
{
	int i = 1;
	t_env *start;
	
	start = env;
	while(process->cmd[i])
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
						break;
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
	return;
}