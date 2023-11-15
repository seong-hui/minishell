/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:54:10 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/15 14:49:44 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void	print_pwd_error(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("pwd: ", 2);
	perror(file);
	g_exit_code = 1;
}

void	print_cd_error(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("cd: ", 2);
	perror(file);
	g_exit_code = 1;
}
