#include "../include/parse.h"

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

void	check_redir_files(t_process *process)
{
	int		fd;
	t_redir	*cur_redir;

	fd = 0;
	cur_redir = process->redir;
	while (cur_redir)
	{
		if (cur_redir->type == T_REDIR_INPUT)
			fd = open(cur_redir->file, O_RDONLY);
		else if (cur_redir->type == T_REDIR_OUTPUT)
			fd = open(cur_redir->file, O_WRONLY | O_CREAT, 0644);
		else if (cur_redir->type == T_REDIR_APPEND)
			fd = open(cur_redir->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd < 0)
			return (print_file_error(cur_redir->file));
		cur_redir = cur_redir->next;
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
			while (in_charset(process->cmd_line[st], " \n\t"))
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
