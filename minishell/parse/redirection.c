/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 22:13:58 by jooypark          #+#    #+#             */
/*   Updated: 2023/11/06 19:39:37 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	add_redir(t_redir **redir, char *file, int type)
{
	t_redir	*new_redir;
	t_redir	*last_redir;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	if (!new_redir)
		exit (1);
	new_redir->type = type;
	new_redir->file = file;
	new_redir->tmp = NULL;
	new_redir->next = NULL;
	if (*redir != NULL)
	{
		last_redir = *redir;
		while (last_redir->next)
			last_redir = last_redir->next;
		last_redir->next = new_redir;
	}
	else
		*redir = new_redir;
}

int	is_redir(char *line)
{
	if (ft_strncmp(line, "<<", 2) == 0)
		return (T_REDIR_HEREDOC);
	else if (ft_strncmp(line, ">>", 2) == 0)
		return (T_REDIR_APPEND);
	else if (*line == '<')
		return (T_REDIR_INPUT);
	else if (*line == '>')
		return (T_REDIR_OUTPUT);
	else
		return (0);
}

int	get_file_len(char *line)
{
	int	i;
	int	in_quote;

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
		else if (in_charset(line[i], " \n\t<>") && in_quote == 0)
			return (i);
		i++;
	}
	return (i);
}

int	get_file_loc(char *line, int type)
{	
	int	i;

	i = 0;
	if (type == T_REDIR_HEREDOC || type == T_REDIR_APPEND)
		i += 2;
	else if (type == T_REDIR_INPUT || type == T_REDIR_OUTPUT)
		i++;
	while (in_charset(line[i], " \n\t"))
		i++;
	return (i);
}

void	parse_redir(t_process *process)
{
	int	i;
	int	st;
	int	type;
	int	len;

	i = 0;
	type = 0;
	while (process->cmd_line[i])
	{
		type = is_redir(&(process->cmd_line[i]));
		if (type != 0)
		{
			st = i + get_file_loc(&(process->cmd_line[i]), type);
			len = get_file_len(&(process->cmd_line[st]));
			add_redir(&(process->redir),
				ft_strndup(&(process->cmd_line[st]), len), type);
			while (i < st + len)
				process->cmd_line[i++] = ' ';
		}
		else
			i++;
	}
}
