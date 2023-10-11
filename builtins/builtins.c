/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:22:14 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/11 17:45:34 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "stdio.h"

void	check_biltins(char **token)
{
	int i = 0;
	while(token[i])
	{
		printf("%s\n", token[i]);
		i++;
	}
	
	if (!ft_strncmp(token[0], "echo", ft_strlen("echo")))
		builtin_echo(token);
	// else if (!ft_strncmp(token[0], "cd", ft_strlen("cd")))
	// 	builtin_cd(token);
	// else if (!ft_strncmp(token[0], "pwd", ft_strlen("pwd")))
	// 	builtin_pwd(token);
	// else if (!ft_strncmp(token[0], "export", ft_strlen("export")))
	// 	builtin_export(token);
	// else if (!ft_strncmp(token[0], "unset", ft_strlen("unset")))
	// 	builtin_unset(token);
	// else if (!ft_strncmp(token[0], "env", ft_strlen("env")))
	// 	builtin_env(token);
	// else if (!ft_strncmp(token[0], "exit", ft_strlen("exit")))
	// 	builtin_exit(token);
}

int main(int ac, char **av)
{
	//av++;
	(void)ac;
	check_biltins(av + 1);
}