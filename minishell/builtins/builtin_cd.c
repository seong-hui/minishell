/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:24:50 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/05 19:54:29 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void	update_pwd(t_env *env, char *old_pwd)
{
	char	*pwd;

	replace_env(&env, "OLDPWD", old_pwd);
	pwd = getcwd(NULL, 0);
	if (pwd)
		replace_env(&env, "PWD", pwd);
}

void	update_oldpwd(t_env *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		replace_env(&env, "OLDPWD", pwd);
	}
}

char	*get_cur_dir(void)
{
	char	*cur_dir;

	cur_dir = getcwd(NULL, 0);
	if (!cur_dir)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(cur_dir);
	}
	return (cur_dir);
}

void	handle_home_error(t_env *env, char *old_pwd)
{
	if (chdir(search_env_value(&env, "HOME")) != 0)
	{
		if (!search_env_value(&env, "HOME"))
			ft_putendl_fd("minishell: cd: HOME not set", 2);
		else
		{
			ft_putstr_fd("minishell: cd: ", 2);
			perror(search_env_value(&env, "HOME"));
		}
	}
	else
		update_pwd(env, old_pwd);
}

void	builtin_cd(t_process *process, t_env *env)
{
	char	*path;
	char	*cur_dir;
	char	*old_pwd;

	g_exit_code = 0;
	old_pwd = search_env_value(&env, "PWD");
	if (!old_pwd)
		old_pwd = getcwd(NULL, 0);
	path = process->cmd[1];
	if (path == NULL || *path == '\0')
		handle_home_error(env, old_pwd);
	else
	{
		cur_dir = get_cur_dir();
		if (chdir(path) != 0)
			print_cd_error(path);
		update_pwd(env, old_pwd);
	}
}
