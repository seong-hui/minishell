/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:41:14 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/15 16:35:27 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	exit_and_setcode(void)
{
	g_exit_code = 1;
	exit(g_exit_code);
}

void	close_fd(t_process *process)
{
	if (process->infile_fd != STDIN_FILENO)
		close(process->infile_fd);
	if (process->outfile_fd != STDOUT_FILENO)
		close(process->outfile_fd);
}

void	util_write(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(2, str, len);
}
