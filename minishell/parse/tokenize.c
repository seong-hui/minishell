
#include "../include/parse.h"

void	print_lists(t_process **process, t_env **env);

void	add_process(t_process **process, char *cmd_line)
{
	t_process *new_process;
	t_process	*last_process;

	new_process = (t_process *)malloc(sizeof(t_process));
	new_process->redir = NULL;
	new_process->cmd_line = cmd_line;
	new_process->cmd = NULL;
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

int	is_all_blank(char *line)
{
	int	i;
	int	blank;

	i = 0;
	blank = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\n' || line[i] == '\t')
			blank++;
		i++;
	}
	if (i != blank)
		return (0);
	return (1);
}

void	split_process(t_process **process, char *line)
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
			return (print_syntax_error("invalid syntax"));
		line[i + pipe] = '\0';
		if (!is_all_blank(&line[i]))
			add_process(process, ft_strdup(&line[i]));
		else
			return (print_syntax_error("invalid syntax"));
		i += pipe;
		if (i != line_len)
			i++;
	}
}

void	check_quote(char *line)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (quote == 0)
				quote = line[i];
			else if (line[i] == quote)
				quote = 0;
		}
		i++;
	}
	if (quote != 0)
		print_syntax_error("quote not closed");
}

int	tokenize(t_process **process, t_env **env, char *line)
{
	t_process	*cur;

	if (is_all_blank(line))
		return (0);
	check_quote(line);
	if (g_exit_code != 0)
		return (0);
	split_process(process, line);
	if (g_exit_code != 0)
		return (0);
	cur = *process;
	while (cur)
	{
		parse_redir(cur);
		parse_cmd(cur);
		replace_process_resources(cur, env);
		check_syntax(cur);
		if (g_exit_code != 0)
			return (0);
		check_redir_files(cur);
		if (g_exit_code != 0)
			return (0);
		cur = cur->next;
	}
	return (1);
}
