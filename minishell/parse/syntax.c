/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:28:07 by jooypark          #+#    #+#             */
/*   Updated: 2023/11/05 20:48:51 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	print_syntax_error(char *str)
{
	ft_putstr_fd("minishell: syntax error: ", 2);
	ft_putendl_fd(str, 2);
	g_exit_code = 258;
}

int	check_syntax(t_process **process)
{
	t_process	*cur;
	t_redir		*cur_redir;

	cur = *process;
	while (cur)
	{
		cur_redir = cur->redir;
		while (cur_redir)
		{
			if (cur_redir->file == NULL || cur_redir->file[0] == '\0')
				return (print_syntax_error("invalid syntax"), 0);
			cur_redir = cur_redir->next;
		}
		cur = cur->next;
	}
	return (1);
}
