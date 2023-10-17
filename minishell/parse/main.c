/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:43:33 by jooypark          #+#    #+#             */
/*   Updated: 2023/10/17 22:32:32 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	print_lists(t_process *process, t_env *env)
{
	int	i = 1;
	t_redir *cur_redir;
	printf("\n[[PROCESS LIST]]\n\n");
	while (process)
	{
		printf("[PROCESS %d]\n", i);
		printf("cmd_line: %s\n", process->cmd_line);
		printf("[PROCESS %d - REDIR]\n", i);
		cur_redir = process->redir;
		if (cur_redir == NULL)
			printf("No Redirection\n");
		while (cur_redir)
		{
			printf("type: %d, file: %s\n", cur_redir->type, cur_redir->file);
			cur_redir = cur_redir->next;
		}
		printf("[PROCESS %d - CMD]\n", i++);
		if (process->cmd == NULL)
			printf("No Cmd\n");
		while (*process->cmd)
		{
			printf("cmd: %s\n", *process->cmd);
			process->cmd++;
		}
		printf("\n");
		process = process->next;
	}
	//printf("\n[[ENV LIST]]\n\n");
	while (env)
	{
		//printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_process	*process;
	t_env		*env;

	ac = 0;
	av = NULL;
	while (1)
	{
		process = NULL;
		env = NULL;
		line = readline("minishell$ ");
		add_history(line);
		tokenize(&process, &env, line, envp);
		//print_lists(process, env);
		process_start(process, envp);
		free(line);
	}
}
