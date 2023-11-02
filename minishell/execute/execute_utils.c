/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:21:18 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/02 21:50:23 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	ft_lstsize(t_process *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

char	*get_cmd(char **path, char *cmd)
{
	int		i;
	char	*tmp_cmd;
	int		fd;
	char	*tmp;

	i = 0;
	fd = access(cmd, X_OK);
	if (fd != -1)
		return (ft_strdup(cmd));
	tmp_cmd = ft_strjoin("/", cmd);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], tmp_cmd);
		fd = access(tmp, X_OK);
		if (fd != -1)
		{
			free(tmp_cmd);
			return (tmp);
		}
		close(fd);
		free(tmp);
		i++;
	}
	free(tmp_cmd);
	return (0);
}

char	**get_path(t_env *env)
{
	char	**path;

	path = NULL;
	while (env)
	{
		if (ft_strncmp("PATH", env->key, 4) == 0)
		{
			path = ft_split(env->value, ':');
			break ;
		}
		env = env->next;
	}
	return (path);
}
