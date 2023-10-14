/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:22:14 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/14 20:20:53 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	check_biltins(t_process *process)
{
	if (!ft_strncmp(process->cmd[0], "echo", ft_strlen("echo")))
		builtin_echo(process);
	else if (!ft_strncmp(process->cmd[0], "cd", ft_strlen("cd")))
		builtin_cd(process);
	else if (!ft_strncmp(process->cmd[0], "pwd", ft_strlen("pwd")))
		builtin_pwd(process);
	// else if (!ft_strncmp(token[0], "export", ft_strlen("export")))
	// 	builtin_export(token);
	// else if (!ft_strncmp(token[0], "unset", ft_strlen("unset")))
	// 	builtin_unset(token);
	// else if (!ft_strncmp(token[0], "env", ft_strlen("env")))
	// 	builtin_env(token);
	// else if (!ft_strncmp(token[0], "exit", ft_strlen("exit")))
		// builtin_exit(token);
}

int main(int ac, char **av)
{
    (void)ac; 

    t_process process;
    t_redir redir;

	char **cmd = (char **)malloc(sizeof(char *) * ac); 

	int i = 1;
   while(i <= ac) {
        cmd[i - 1] = av[i];
		i++;
    }
    cmd[i - 1] = NULL; 
    redir.type = T_REDIR_OUTPUT;
    redir.file = "output.txt";
    redir.tmp = NULL;


    process.redir = &redir; 
	process.cmd = cmd;
    process.next = NULL; 

	// for(int j = 0; j < ac; j++)
	// {
	// 	printf("%s\n",process.cmd[j]);
	// }

	check_biltins(&process);

    return 0;
}