/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:44:23 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/04 16:24:48 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void	print_exit_error1(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("numeric argument required", 2);
	g_exit_code = 255;
}

void	print_exit_error2(void)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("too many argument", 2);
	g_exit_code = 1;
}

void	print_export_error(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd("not a valid identifier", 2);
	g_exit_code = 1;
}

void	print_unset_error(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd("not a valid identifier", 2);
	g_exit_code = 1;
}
