/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:03:14 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/24 21:08:07 by seonghmo         ###   ########.fr       */
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
				while (env)
				{
					if (!ft_strcmp(env->key, process->cmd[i]))
						delete_env(env, env->key);
					else
						env = env->next;
				}
			
			}
		else
		{
			ft_putchar_fd(process->cmd[i], fd);
			ft_putchar_fd(": not a valid identifier", fd);
			perror(process->cmd[i]);
		}
		i++;
	}
	return;
}