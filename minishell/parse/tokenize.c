
#include "../include/parse.h"

int	is_all_blank(char *line)
{
	int	i;
	int	blank;

	i = 0;
	blank = 0;
	while (line[i])
	{
		if (in_charset(line[i], " \n\t"))
			blank++;
		i++;
	}
	if (i != blank)
		return (0);
	return (1);
}

int	is_quote_closed(char *line)
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
		return (print_syntax_error("quote not closed"), 0);
	return (1);
}

int	tokenize(t_process **process, t_env **env, char *line)
{
	t_process	*cur;

	if (is_all_blank(line))
		return (0);
	if (!is_quote_closed(line))
		return (0);
	if (!split_process(process, line))
		return (0);
	cur = *process;
	while (cur)
	{
		parse_redir(cur);
		parse_cmd(cur);
		replace_process_resources(cur, env);
		cur = cur->next;
	}
	if (!check_syntax(process))
		return (0);
	return (1);
}
