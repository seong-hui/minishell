/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:43:33 by jooypark          #+#    #+#             */
/*   Updated: 2023/11/13 20:41:18 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

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
		add_history(line);
		if (tokenize(&process, &env, line) == 1)
		{
			g_exit_code = 0;
			process_start(process, env, envp);
		}
		free_process_list(&process);
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env		*env;

	av = NULL;
	env = NULL;
	if (ac == 1)
	{
		create_env_list(&env, envp);
		detect_signal();
		set_terminal_print_off();
		run_prompt(env, envp);
		set_terminal_print_on();
		free_env_list(env);
	}
	return (0);
}
