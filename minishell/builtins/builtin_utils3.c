/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:38:29 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/08 15:46:38 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	search_env_key(t_env **env, char *search)
{
	t_env	*target;

	target = *env;
	while (target)
	{
		if (ft_strcmp(target->key, search) == 0)
			return (1);
		target = target->next;
	}
	return (0);
}

int	check_vaild_key(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}
