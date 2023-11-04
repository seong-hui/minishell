/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:24:50 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/04 17:10:30 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

char	*get_cur_dir(void)
{
	char	*cur_dir;

	cur_dir = getcwd(NULL, 0);
	if (!cur_dir)
		perror("minishell : getcwd");
	return (cur_dir);
}

void	builtin_cd(t_process *process)
{
	char	*path;
	char	*cur_dir;

	path = process->cmd[1];
	if (path == NULL || *path == '\0')
	{
		if (chdir(getenv("HOME")) != 0)
			perror("minicshell : chdir");
	}
	else
	{
		if (chdir(path) != 0)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			perror(path);
		}
	}
}
