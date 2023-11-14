/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 22:13:58 by jooypark          #+#    #+#             */
/*   Updated: 2023/11/14 22:07:45 by jooypark         ###   ########seoul.kr  */
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
	int	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (is_quote(line[i]))
		{
			if (quote == 0)
				quote = line[i];
			else if (quote == line[i])
				quote = 0;
		}
		else if (in_charset(line[i], " \n\t<>") && quote == 0)
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
	t_parse	re;
	int		st;
	int		type;

	init_parse(&re, process->cmd_line);
	while (re.cmd[re.idx])
	{
		if (is_quote(re.cmd[re.idx]) && re.quote == 0)
			re.quote = re.cmd[re.idx];
		else if (is_quote(re.cmd[re.idx]) && re.quote == re.cmd[re.idx])
			re.quote = 0;
		type = is_redir(&(re.cmd[re.idx]));
		if (type != 0 && re.quote == 0)
		{
			st = re.idx + get_file_loc(&(re.cmd[re.idx]), type);
			re.len = get_file_len(&(re.cmd[st]));
			add_redir(&(process->redir),
				ft_strndup(&(re.cmd[st]), re.len), type);
			while (re.idx < st + re.len)
				re.cmd[(re.idx)++] = ' ';
		}
		else
			re.idx++;
	}
}
