/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 22:04:44 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/09 16:03:02 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void	replace_env(t_env **env, char *key, char *value)
{
	t_env	*tmp_env;

	tmp_env = *env;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->key, key) == 0)
		{
			free(tmp_env->value);
			tmp_env->value = value;
			break ;
		}
		tmp_env = tmp_env->next;
	}
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

void	replace_env_value(t_env **env, char *key, char *value, int equl)
{
	t_env	*tmp_env;

	tmp_env = *env;
	if (equl)
	{
		while (tmp_env)
		{
			if (ft_strcmp(tmp_env->key, key) == 0)
			{
				free(tmp_env->value);
				free(key);
				tmp_env->value = value;
				tmp_env->equal_sign = equl;
				break ;
			}
			tmp_env = tmp_env->next;
		}
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
