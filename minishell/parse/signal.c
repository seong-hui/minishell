/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:57:13 by jooypark          #+#    #+#             */
/*   Updated: 2023/11/13 22:55:11 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 1;
	}
	else if (signo == SIGTERM)
	{
		printf("\033[1A");
		printf("\033[10C");
		printf(" exit\n");
		exit(g_exit_code);
	}
}

void	exec_signal(int signo)
{
	if (signo == SIGINT)
		g_exit_code = 1;
	else if (signo == SIGQUIT)
		printf("^\\Quit: %d\n", signo);
}

void	heredoc_signal(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		g_exit_code = 1;
		exit(1);
	}
	else if (signo == SIGTERM)
	{
		g_exit_code = 0;
		exit(0);
	}
}

void	detect_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_signal(void)
{
	signal(SIGINT, exec_signal);
	signal(SIGQUIT, exec_signal);
}
