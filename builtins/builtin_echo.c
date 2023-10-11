/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:27:04 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/11 19:31:19 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_option(char **token)
{
	char	**cmd;
	int		cmd_cnt;

	cmd = ft_split(token[0], ' ');
	cmd_cnt = 0;
	while (cmd && cmd[cmd_cnt])
		cmd_cnt++;
	if (cmd_cnt > 0)
	{
		if (!ft_strncmp(cmd[1], "-n", ft_strlen("-n")))
			return (1);
	}
	return (0);
}

void	builtin_echo(char **token)
{
	int		i;

	i = 1;
	while (token[i])
	{
		write(1, token[i], ft_strlen(token[i]));
		if (check_option(token))
			write(1, "\n", 1);
		i++;
	}
}
