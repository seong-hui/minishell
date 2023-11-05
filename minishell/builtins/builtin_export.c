/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:33:09 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/05 16:46:13 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void	handle_exception(t_process *process, int i)
{
	if ((process->cmd[i][0] == '_' && !process->cmd[i][1]))
	{
		g_exit_code = 0;
		return ;
	}
	else
		print_export_error(process->cmd[i]);
}

void	handle_edit_env(t_env *env, char *key, char *value, int equl)
{
	if (!ft_strcmp(key, "_"))
	{
		g_exit_code = 0;
		return ;
	}
	if (search_env_key(&env, key))
		replace_env_value(&env, key, value, equl);
	else
		add_env(&env, key, value, equl);
	g_exit_code = 0;
}

void	add_export(t_process *process, t_env *env)
{
	int		i;
	char	*key;
	char	*value;
	int		equl;

	i = 0;
	equl = 0;
	value = NULL;
	while (process->cmd[++i])
	{
		key = get_path_key(process->cmd[i]);
		if (ft_strlen(process->cmd[i]) >= ft_strlen(key) + 1)
		{
			value = get_path_value(&process->cmd[i][ft_strlen(key) + 1]);
			equl = 1;
		}
		if ((process->cmd[i][0] == '_' && process->cmd[i][1])
			|| ft_isalpha(process->cmd[i][0]))
			handle_edit_env(env, key, value, equl);
		else
			handle_exception(process, i);
	}
}

void	copy_key_value(t_env *env, t_env *new_env)
{
	if (env->key)
		new_env->key = ft_strdup(env->key);
	else
		new_env->key = NULL;
	if (env->value)
		new_env->value = ft_strdup(env->value);
	else
		new_env->value = NULL;
	new_env->equal_sign = env->equal_sign;
}

void	builtin_export(t_process *process, t_env *env, int fd, t_excute e_info)
{
	t_env	*env_s;

	env_s = env;
	if (!process->cmd[1])
	{
		env_s = copy_env(env_s);
		env_s = sort_list(env_s);
		while (env_s)
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(env_s->key, fd);
			if (env_s->equal_sign)
			{
				ft_putstr_fd("=", fd);
				ft_putstr_fd("\"", fd);
				ft_putstr_fd(env_s->value, fd);
				ft_putstr_fd("\"", fd);
			}
			ft_putstr_fd("\n", fd);
			env_s = env_s->next;
		}
	}
	else if (e_info.cmd_size == 1)
		add_export(process, env);
}
