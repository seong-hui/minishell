/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:11:45 by seonghmo          #+#    #+#             */
/*   Updated: 2023/11/09 17:53:47 by moonseonghu      ###   ########.fr       */
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
			g_exit_code = exit_code >> 8;
			return (1);
		}
	}
	return (0);
}
