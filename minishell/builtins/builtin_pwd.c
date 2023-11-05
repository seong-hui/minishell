/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:16:33 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/05 19:51:17 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void	builtin_pwd(int fd, t_env *env)
{
	char	*pwd;
	t_env	*copy;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putendl_fd(pwd, fd);
		free(pwd);
		g_exit_code = 0;
	}
	else
		print_pwd_error(pwd);
	return ;
}
