/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:43:33 by jooypark          #+#    #+#             */
/*   Updated: 2023/10/24 20:52:44 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	print_lists(t_process **process, t_env **env)
{
	int	i = 1;
	t_process *cur_process = *process;
	t_redir *cur_redir;
	printf("\n[[PROCESS LIST]]\n\n");
	while (cur_process)
	{
		printf("[PROCESS %d]\n", i);
		printf("cmd_line: %s\n", cur_process->cmd_line);
		printf("[PROCESS %d - REDIR]\n", i);
		cur_redir = cur_process->redir;
		if (cur_redir == NULL)
			printf("No Redirection\n");
		while (cur_redir)
		{
			printf("type: %d, file: %s\n", cur_redir->type, cur_redir->file);
			cur_redir = cur_redir->next;
		}
		printf("[PROCESS %d - CMD]\n", i++);
		if (cur_process->cmd == NULL)
			printf("No Cmd\n");
		int	idx = 0;
		while (cur_process->cmd && cur_process->cmd[idx])
			printf("cmd: %s\n", cur_process->cmd[idx++]);
		printf("\n");
		cur_process = cur_process->next;
	}
	t_env *cur_env = *env;
	printf("\n[[ENV LIST]]\n\n");
	while (cur_env)
	{
		printf("%s=%s\n", cur_env->key, cur_env->value);
		cur_env = cur_env->next;
	}
}

void	cl()
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_process	*process;
	t_env		*env;

	//atexit(cl);
	ac = 0;
	av = NULL;
	env = NULL;
	create_env_list(&env, envp);
	detect_signal();
	set_terminal_print_off();
	while (1)
	{
		g_exit_code = 0;
		process = NULL;
		line = readline("minishell$ ");
		if (!line)
			signal_handler(SIGTERM);
		add_history(line);
		// if (tokenize(&process, &env, line) == 1)
		// 	print_lists(&process, &env);
		if (tokenize(&process, &env, line) == 1)
			process_start(process, env, envp);
		//print_lists(&process, &env);
		free_process_list(&process);
		//process_start(process, envp);
		free(line);
	}
	free_env_list(env);
	return (0);
}
