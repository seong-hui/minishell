/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:33:09 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/24 21:42:51 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

t_env* sort_list(t_env *env)
{
	t_env *start;
	char *tmp;
	
	start = env;
	while(env->next)
	{
		if (ft_strcmp(env->key, env->next->key) > 0)
		{
			tmp = env->key;
			env->key = env->next->key;
			env->next->key = tmp;
			env = start;
		}
		else
			env = env->next;
	}
	env = start;
	return(env);
}

void check_value(char *env_str)
{
	int	i;

	i = 0;
	while(env_str[i])
	{
		if (env_str[i] == '=')
			return;
	}
}

void add_export(t_process *process, t_env *env)
{
	int i;

	i = 0;
	char *key;
	char *value;
	char **tmp;
	while(process->cmd[i])
	{
		check_value(process->cmd[i]);
		
		if ((process->cmd[i][0] == '_' && process->cmd[i][1]) 
			|| ft_isalpha(process->cmd[i][0]))
		{
			add_env(env, process->cmd[i], process->cmd[i]);
		}
	}
}

void	builtin_export(t_process *process, t_env *env, int fd)
{
	t_env *env_s;
	env_s = env;
	env_s = sort_list(env_s);
	if (!process->next)
	{
	 	while (env_s)
    	{
			ft_putstr_fd("declare -x ", fd);
         	ft_putstr_fd(env_s->key, fd);
         	ft_putstr_fd("=", fd);
			 ft_putstr_fd("\"", fd);
         	ft_putstr_fd(env_s->value, fd);
		 	ft_putendl_fd("\"", fd);
        	env_s = env_s->next;
    	}
	}
	else
	{
		add_export(process, env);
	}
}
