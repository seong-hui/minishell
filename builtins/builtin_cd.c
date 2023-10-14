/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:24:50 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/14 21:42:30 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_command(char *command)
{
	char *cur_dir;
	char *par_dir;
	char *last_slash;

    par_dir = (char *)malloc(1024);

    if (par_dir == NULL) {
        perror("malloc");
        exit(1);
    }

	if (ft_strncmp(command, "..", ft_strlen("..")))
		return (0);
	cur_dir = getcwd(NULL, 0);
	if (!cur_dir)
	{
        perror("getcwd");
        exit(1);
    }
	last_slash = ft_strrchr(cur_dir, '/');
	if (last_slash)
	{
		ft_strncpy(par_dir, cur_dir, last_slash - cur_dir);
        par_dir[last_slash - cur_dir] = '\0';
    }

	 if (chdir(par_dir) != 0) {
        perror("chdir");
        exit(1);
    }

    printf("Current directory: %s\n", par_dir);

	return (1);
}

void builtin_cd(t_process *process)
{
	char *path;

	path = process->cmd[1];
	if (path == NULL || *path == '\0')
	{
		if (chdir(getenv("HOME")) != 0)
			perror("chdir");
	}
	else
	{
		if (! check_command(process->cmd[1]))
		{
		if (chdir(path) != 0)
			perror(path); 
		}
	}
}
