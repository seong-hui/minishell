/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:21:18 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/14 19:16:07 by jooypark         ###   ########seoul.kr  */
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
	while (path && path[i])
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
	return (NULL);
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

void	unlink_file(t_redir *redir)
{
	while (redir)
	{
		if (redir->tmp)
			unlink(redir->tmp);
		redir = redir->next;
	}
}

char	**copy_envp(char **envp)
{
	int		i;
	char	**tmp;
	char	**start;

	i = 0;
	tmp = NULL;
	start = tmp;
	while (envp[i])
	{
		tmp[i] = ft_strdup(envp[i]);
		i++;
	}
	tmp = start;
	return (tmp);
}
