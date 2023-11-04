/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:33:09 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/04 16:22:09 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void	replace_env(t_env **env, char *key, char *value)
{
	t_env	*tmp_env;

	tmp_env = *env;
	if (value)
	{
		while (tmp_env)
		{
			if (ft_strcmp(tmp_env->key, key) == 0)
			{
				tmp_env->value = value;
				break ;
			}
			tmp_env = tmp_env->next;
		}
	}
}

void	add_export(t_process *process, t_env *env)
{
	int		i;
	char	*key;
	char	*value;
	char	*cmd;

	i = 0;
	while (process->cmd[++i])
	{
		cmd = process->cmd[i];
		key = get_path_key(cmd);
		if (ft_strlen(process->cmd[i]) > ft_strlen(key) + 1)
			value = get_path_value(&process->cmd[i][ft_strlen(key) + 1]);
		else
			value = NULL;
		if ((process->cmd[i][0] == '_' && process->cmd[i][1]) 
			|| ft_isalpha(process->cmd[i][0]))
		{
			if (search_env_key(&env, key))
				replace_env(&env, key, value);
			else
				add_env(&env, key, value);
		}
		else
			print_export_error(process->cmd[i]);
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
}

t_env	*copy_env(t_env *env)
{
	t_env	*copy;
	t_env	*new_env;
	t_env	*temp;

	copy = NULL;
	while (env)
	{
		new_env = (t_env *)malloc(sizeof(t_env));
		if (!new_env)
			exit(1);
		copy_key_value(env, new_env);
		new_env->next = NULL;
		if (copy == NULL)
			copy = new_env;
		else
		{
			temp = copy;
			while (temp->next)
				temp = temp->next;
			temp->next = new_env;
		}
		env = env->next;
	}
	return (copy);
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
			if (env_s->value)
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
