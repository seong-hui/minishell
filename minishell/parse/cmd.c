/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:17:01 by jooypark          #+#    #+#             */
/*   Updated: 2023/11/04 21:38:34 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

int	skip_quote(char *line)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	if (line[i] == '\'' || line[i] == '"')
	{
		quote = line[i++];
		while (quote != line[i])
			i++;
	}
	return (i);
}

int	count_cmd(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (line[i] && in_charset(line[i], " \n\t"))
			i++;
		if (line[i] && !in_charset(line[i], " \n\t"))
			count++;
		while (line[i] && !in_charset(line[i], " \n\t"))
		{
			i += skip_quote(&line[i]);
			i++;
		}
	}
	return (count);
}

char	*add_new_cmd(char *line)
{
	int		i;
	int		len;
	char	*new_cmd;

	len = 0;
	while (line[len] && !in_charset(line[len], " \n\t"))
	{
		len += skip_quote(&line[len]);
		len++;
	}
	new_cmd = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		new_cmd[i] = line[i];
		i++;
	}
	new_cmd[i] = 0;
	return (new_cmd);
}

void	parse_cmd(t_process *process)
{
	int	i;
	int	j;
	int	count;

	count = count_cmd(process->cmd_line);
	process->cmd = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	j = 0;
	while (j < count)
	{
		while (in_charset(process->cmd_line[i], " \n\t"))
			i++;
		if (process->cmd_line[i])
			process->cmd[j++] = add_new_cmd(&process->cmd_line[i]);
		while (process->cmd_line[i] && !in_charset(process->cmd_line[i], " \n\t"))
		{
			i += skip_quote(&process->cmd_line[i]);
			i++;
		}
	}
	process->cmd[j] = NULL;
}
