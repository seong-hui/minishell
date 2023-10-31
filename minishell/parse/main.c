/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:43:33 by jooypark          #+#    #+#             */
/*   Updated: 2023/10/31 22:09:01 by seonghmo         ###   ########.fr       */
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



void	minishell_exit(void)
{
	write(2, "\033[1A", 4);
	write(2, "\033[11C", 5);
	write(2, "exit\n", 5);
	set_terminal_print_on();
	exit(g_exit_code = 0);
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
	//정재윤이 추가한 부분 -> while문 들어가기 전에 시그널 처리 한 번 해야됨.
	//쭈영 질문 예상 -> 왜 그렇게 해야돼?
	//전체적으로 시그널을 만들어준 다음 히어독 or execve에서 입력을 받을 때 시그널 처리가 다르기 때문에
	//heredoc 함수나 pipe 함수에 들어가서 다시 시그널 처리를 해줄거임
	//signal_handler(SIGTERM);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		process = NULL;
		line = readline("minishell$ ");
		if (!line)
			signal_handler(SIGTERM);
		add_history(line);
		if (tokenize(&process, &env, line) == 1)
			process_start(process, env, envp);
		//print_lists(&process, &env);
		free_process_list(&process);
		free(line);
	}
	set_terminal_print_on();
	free_env_list(env);
	return (0);
}
