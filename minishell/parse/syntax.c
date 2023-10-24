/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:28:07 by jooypark          #+#    #+#             */
/*   Updated: 2023/10/24 21:24:20 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	print_syntax_error(char *str)
{
	ft_putstr_fd("minishell: syntax error: ", 2);
	ft_putendl_fd(str, 2);
	g_exit_code = 258;
}

void	check_syntax(t_process *process)
{
	t_redir	*cur_redir;

	if (process == NULL || process->cmd == NULL || process->cmd[0] == NULL
		|| process->cmd[0][0] == '\0')
		return (print_syntax_error("invalid syntax"));
	cur_redir = process->redir;
	while (cur_redir)
	{
		if (cur_redir->file == NULL || cur_redir->file[0] == '\0')
			return (print_syntax_error("invalid syntax"));
		cur_redir = cur_redir->next;
	}
}

