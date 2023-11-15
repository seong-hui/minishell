/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:34:19 by jooypark          #+#    #+#             */
/*   Updated: 2023/11/15 17:00:02 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	print_file_error(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("No such file or directory", 2);
	g_exit_code = 1;
	exit(g_exit_code);
}

static void	print_command_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("command not found", 2);
	g_exit_code = 127;
	exit(g_exit_code);
}

static int	exception_handle_dot(char *cmd)
{
	if (cmd[0] == '.' && ft_strlen(cmd) == 1)
	{
		util_write("minishell: ");
		util_write(".: filename argument required\n");
		util_write(".: usage: . filename [arguments]\n");
		g_exit_code = 2;
		return (1);
	}
	return (0);
}

static void	handle_error_print(char *cmd, char *error_str, int e_code)
{
	util_write("minishell: ");
	write(1, cmd, ft_strlen(cmd));
	util_write(error_str);
	g_exit_code = e_code;
}

void	evecve_error(char *cmd)
{
	struct stat	t_stat;

	if (cmd[0] == '\0')
	{
		g_exit_code = 0;
		exit(g_exit_code);
	}
	stat(cmd, &t_stat);
	if (exception_handle_dot(cmd))
		exit(g_exit_code);
	if (S_ISDIR(t_stat.st_mode) && (!ft_strncmp(cmd, "/Users", 5)
			|| (cmd[0] == '.' && cmd[1] == '/')))
		handle_error_print(cmd, ": is a directory\n", 126);
	else if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/')
	{
		if (access(cmd, F_OK) < 0)
			handle_error_print(cmd, ": No such file or directory\n", 127);
		else if (access(cmd, X_OK) < 0)
			handle_error_print(cmd, ": Permission denied\n", 126);
	}
	else
		print_command_error(cmd);
	exit(g_exit_code);
}
