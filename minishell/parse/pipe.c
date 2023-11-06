/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 22:16:55 by jooypark          #+#    #+#             */
/*   Updated: 2023/11/06 19:58:53 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	add_process(t_process **process, char *cmd_line)
{
	t_process	*new_process;
	t_process	*last_process;

	new_process = (t_process *)malloc(sizeof(t_process));
	if (!new_process)
		exit(1);
	new_process->redir = NULL;
	new_process->cmd = NULL;
	new_process->cmd_line = cmd_line;
	new_process->cmd_path = NULL;
	new_process->infile_fd = 0;
	new_process->outfile_fd = 0;
	new_process->next = NULL;
	if (*process != NULL)
	{
		last_process = *process;
		while (last_process->next)
			last_process = last_process->next;
		last_process->next = new_process;
	}
	else
		*process = new_process;
}

int	skip_quote_with_pipe(char *line)
{
	int	in_quote;
	int	i;

	i = 0;
	in_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (in_quote == 0)
				in_quote = line[i];
			else if (in_quote == line[i])
				in_quote = 0;
		}
		if (line[i] && line[i] == '|' && in_quote == 0)
			return (i);
		i++;
	}
	return (i);
}

int	split_process(t_process **process, char *line)
{
	int	i;
	int	pipe;
	int	line_len;

	line_len = ft_strlen(line);
	i = 0;
	while (line[i])
	{
		pipe = skip_quote_with_pipe(&line[i]);
		if (line[i + pipe] == '|' && !line[i + pipe + 1])
			return (print_syntax_error("invalid syntax"), 0);
		line[i + pipe] = '\0';
		if (!is_all_blank(&line[i]))
			add_process(process, ft_strdup(&line[i]));
		else
			return (print_syntax_error("invalid syntax"), 0);
		i += pipe;
		if (i != line_len)
			i++;
	}
	return (1);
}
