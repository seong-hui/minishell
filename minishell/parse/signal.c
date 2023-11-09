/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 21:57:13 by jooypark          #+#    #+#             */
/*   Updated: 2023/11/09 18:55:08 by moonseonghu      ###   ########.fr       */
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
		exit(0);
	}
}

void	exec_signal(int signo)
{
	if (signo == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		g_exit_code = 1;
	}
	else if (signo == SIGQUIT)
	{
		printf("^\\Quit: %d\n", signo);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	heredoc_signal(int signo)
{
	if (signo == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		printf("\n");
		g_exit_code = 1;
		exit(1);
	}
	else if (signo == SIGTERM)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
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
