/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:06:27 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/08 15:38:45 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int	ft_cmdsize(char **cmd)
{
	int	len;

	len = 0;
	while (cmd[len])
		len++;
	return (len);
}

void	exchange_sign(t_env *env)
{
	int		tmp_sign;

	tmp_sign = env->equal_sign;
	env->equal_sign = env->next->equal_sign;
	env->next->equal_sign = tmp_sign;
}

t_env	*sort_list(t_env *env)
{
	t_env	*start;
	char	*tmp_key;
	char	*tmp_value;

	start = env;
	while (env->next)
	{
		if (ft_strcmp(env->key, env->next->key) > 0)
		{
			tmp_key = env->key;
			tmp_value = env->value;
			env->key = env->next->key;
			env->value = env->next->value;
			env->next->key = tmp_key;
			env->next->value = tmp_value;
			exchange_sign(env);
			env = start;
		}
		else
			env = env->next;
	}
	env = start;
	return (env);
}

void	check_value(char *env_str)
{
	int	i;

	i = 0;
	while (env_str[i])
	{
		if (env_str[i] == '=')
			return ;
	}
}
