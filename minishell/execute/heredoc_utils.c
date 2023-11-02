/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:11:45 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/02 23:13:15 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	wait_child(int i, int exit_code)
{
	while (i > 0)
	{
		wait(&exit_code);
		i--;
	}
}

int	child_exit_status(int exit_code)
{
	if (WIFEXITED(exit_code))
	{
		if (exit_code != 0)
		{
			g_exit_code = exit_code;
			return (1);
		}
	}
	return (0);
}
