#include "parse.h"

int	get_file_len(char *line)
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
		else if ((line[i] == ' ' || line[i] == '\n' || line[i] == '\t'
				|| line[i] == '<' || line[i] == '>') && in_quote == 0)
			return (i);
		i++;
	}
	return (i);
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

void	add_redir(t_redir **redir, char *file, int type)
{
	t_redir *new_redir;
	t_redir	*last_redir;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	new_redir->type = type;
	new_redir->file = file;
	new_redir->next = NULL;
	if (*redir == NULL)
	{
		*redir = new_redir;
		return ;
	}
	else
	{
		last_redir = *redir;
		while (last_redir->next)
			last_redir = last_redir->next;
		last_redir->next = new_redir;
	}
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
			st = i;
			if (type == T_REDIR_HEREDOC || type == T_REDIR_APPEND)
				st += 2;
			else if (type == T_REDIR_INPUT || type == T_REDIR_OUTPUT)
				st++;
			while ((process->cmd_line[st] == ' ' || process->cmd_line[st] == '\n'
					|| process->cmd_line[st] == '\t') && process->cmd_line[st] != 0)
					st++;
			len = get_file_len(&(process->cmd_line[st]));
			add_redir(&(process->redir), ft_strndup(&(process->cmd_line[st]), len), type);
			while (i < st + len)
				process->cmd_line[i++] = ' ';
		}
		else
			i++;
	}
}