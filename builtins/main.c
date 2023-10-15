/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:00:53 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/16 04:38:32 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "builtins.h"



char	**get_path(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
		{
			path = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (path);
}

int main(int ac, char **av, char **envp)
{
    (void)ac; 

    t_process process;
    t_redir redir;

	char **cmd = (char **)malloc(sizeof(char *) * ac);

	int i = 1;
   while(i <= ac)
   {
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
    envp = get_path(envp);
    
	// for(int j = 0; j < ac; j++)
	// {
	// 	printf("%s\n",process.cmd[j]);
	// }
	//check_biltins(&process);
    process_start(&process, envp);

    return 0;
}