/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:00:53 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/17 20:52:43 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/builtins.h"



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
//    while(i <= ac)
//    {
//         cmd[i - 1] = av[i];
// 		i++;
//     }
//     cmd[i - 1] = NULL;
//     redir.type = T_REDIR_OUTPUT;
//     redir.file = "output.txt";
//     redir.tmp = NULL;
//     process.redir = &redir;
// 	process.cmd = cmd;
//     process.next = NULL;
    envp = get_path(envp);

t_redir redir1 = {T_REDIR_INPUT, "infile", NULL, NULL};
t_redir redir2 = {T_REDIR_OUTPUT, "output2.txt", NULL, NULL};
t_redir redir3 = {T_REDIR_INPUT, "input.txt", NULL, NULL};
t_redir redir4 = {T_REDIR_INPUT, "input1.txt", NULL, NULL};

char *cmd1[] = {"ls", "-l", NULL};
char *cmd2[] = {"wc", "-l", NULL};
char *cmd3[] = {"ls",  NULL};
char *cmd4[] = {"ls",  NULL};

t_process process1 = {&redir1, cmd1, NULL, {0, 0}, 0, 0};
t_process process2 = {&redir2, cmd2, NULL, {0, 0}, 0, 0};
t_process process3 = {&redir3, cmd3, NULL, {0, 0}, 0, 0};
t_process process4 = {&redir4, cmd4, NULL, {0, 0}, 0, 0};

process1.next = &process2;
process2.next = &process3;
// process3.next = &process4;
//printf("%d %d %d\n", process1.redir->type, process1.next->redir->type, process1.next->next->redir->type);
    
	// for(int j = 0; j < ac; j++)
	// {
	// 	printf("%s\n",process1.cmd[j]);
	// }
	//check_biltins(&process);
    process_start(&process1, envp);

    return 0;
}