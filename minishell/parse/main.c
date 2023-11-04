/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:43:33 by jooypark          #+#    #+#             */
/*   Updated: 2023/11/04 15:16:10 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	cl()
{
	system("leaks minishell");
}

void	run_prompt(t_env *env, char **envp)
{
	char		*line;
	t_process	*process;

	while (1)
	{
		process = NULL;
		line = readline("minishell$ ");
		if (!line)
			signal_handler(SIGTERM);
		add_history(line);
		if (tokenize(&process, &env, line) == 1)
			process_start(process, env, envp);
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
