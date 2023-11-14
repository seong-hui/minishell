/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:33:09 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/14 15:05:27 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

static void	handle_exception(t_process *process, int i, char *key)
{
	free(key);
	if ((process->cmd[i][0] == '_'
		&& (!process->cmd[i][1] || process->cmd[i][1] == '=')))
	{
		g_exit_code = 0;
		return ;
	}
	else
		print_export_error(process->cmd[i]);
}

static void	handle_edit_env(t_env *env, char *key, char *value, int equl)
{
	if (!ft_strcmp(key, "_"))
	{
		free(key);
		g_exit_code = 0;
		return ;
	}
	if (search_env_key(&env, key))
	{
		replace_env_value(&env, key, value, equl);
		if (!equl)
			free(key);
	}
	else
		add_env(&env, key, value, equl);
}

static void	add_export(t_process *process, t_env *env)
{
	int		i;
	char	*key;
	char	*value;
	int		equl;

	i = 0;
	value = NULL;
	while (process->cmd[++i])
	{
		equl = 0;
		key = get_path_key(process->cmd[i]);
		if (ft_strlen(process->cmd[i]) >= ft_strlen(key) + 1)
		{
			value = get_path_value(&process->cmd[i][ft_strlen(key) + 1]);
			equl = 1;
		}
		if (check_vaild_key(key))
			handle_edit_env(env, key, value, equl);
		else
			handle_exception(process, i, key);
	}
}

static void	export_putstr(t_env *env_s, int fd)
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
}

void	builtin_export(t_process *process, t_env *env, int fd, t_excute e_info)
{
	t_env	*env_s;
	t_env	*start_copy;

	env_s = env;
	if (!process->cmd[1])
	{
		env_s = copy_env(env_s);
		env_s = sort_list(env_s);
		start_copy = env_s;
		while (env_s)
		{
			if (!ft_strcmp(env_s->key, "_"))
			{
				env_s = env_s->next;
				continue ;
			}
			export_putstr(env_s, fd);
			env_s = env_s->next;
		}
		env_s = start_copy;
		free_env_list(env_s);
	}
	else if (e_info.cmd_size == 1)
		add_export(process, env);
}
