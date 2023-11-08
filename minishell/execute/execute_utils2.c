/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:41:14 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/08 15:42:39 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	exit_and_setcode(void)
{
	g_exit_code = 1;
	exit(g_exit_code);
}

int	redir_check(t_process **process, t_excute *exe_info)
{
	t_process	*cur;

	cur = *process;
	if (cur->infile_fd < 0 || cur->outfile_fd < 0)
	{
		exe_info->i += 1;
		cur = cur->next;
		*process = cur;
		return (1);
	}
	return (0);
}
