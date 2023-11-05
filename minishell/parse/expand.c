/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:00:07 by jooypark          #+#    #+#             */
/*   Updated: 2023/11/05 20:46:11 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	init_expand(t_expand *expand, char *str, t_env **env)
{
	expand->cmd = str;
	expand->len = replace_len(str, env);
	expand->idx = 0;
	expand->quote = 0;
}

void	update_quote(char c, int *quote)
{
	if (*quote == 0)
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

int	expand_len(int *len, char *str, t_env **env, int quote)
{
	int		i;
	char	*env_key;
	char	*env_value;

	i = 0;
	env_key = get_env_key(&str[i + 1]);
	if ((ft_strlen(env_key) == 0) && (quote != 0
			|| !(str[i + 1] == '\'' || str[i + 1] == '"')))
		(*len)++;
	else
	{
		if (ft_strcmp(env_key, "?") == 0)
			env_value = ft_itoa((long long)g_exit_code);
		else
			env_value = search_env_value(env, env_key);
		if (env_value != NULL)
			*len += ft_strlen(env_value);
		i += ft_strlen(env_key);
	}
	free(env_key);
	return (i);
}

void	expand_cmd(char *replaced, t_expand *expand, t_env **env)
{
	int		i;
	char	*env_key;
	char	*env_value;

	env_key = get_env_key(expand->cmd + 1);
	if ((ft_strlen(env_key) == 0) && (expand->quote != 0
			|| !(*(expand->cmd + 1) == '\'' || *(expand->cmd + 1) == '"')))
		replaced[expand->idx++] = '$';
	else
	{
		if (ft_strcmp(env_key, "?") == 0)
			env_value = ft_itoa((long long)g_exit_code);
		else
			env_value = search_env_value(env, env_key);
		if (env_value != NULL)
		{
			i = -1;
			while (env_value[++i])
				replaced[expand->idx++] = env_value[i];
			free(env_value);
		}
		expand->cmd += ft_strlen(env_key);
	}
	free(env_key);
}
