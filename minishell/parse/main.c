/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:43:33 by jooypark          #+#    #+#             */
/*   Updated: 2023/11/07 20:09:25 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	process_start(t_process *process, t_env *env, char **envp);

void	cl(void)
{
	system("leaks --list minishell");
}

void	print_process(t_process **process)
{
	t_process *cur = *process;

	while (cur)
	{
		int i = 0;
		while (cur->cmd && cur->cmd[i])
			printf("cmd[%d]: %s\n", i, cur->cmd[i++]);
		cur = cur->next;
	}
}

void	run_prompt(t_env *env, char **envp)
{
	char		*line;
	t_process	*process;

	while (1)
	{
		detect_signal();
		process = NULL;
		line = readline("minishell$ ");
		if (!line)
			signal_handler(SIGTERM);
		//signal(SIGINT, signal_handler);
		add_history(line);
		if (tokenize(&process, &env, line) == 1)
			process_start(process, env, envp);
		//print_process(&process);
		free_process_list(&process);
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env		*env;

	//atexit(cl);
	ac = 0;
	av = NULL;
	env = NULL;
	create_env_list(&env, envp);
	detect_signal();
	set_terminal_print_off();
	run_prompt(env, envp);
	set_terminal_print_on();
	free_env_list(env);
	return (0);
}
