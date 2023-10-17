#include "parse.h"

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

void	split_process(t_process **process, char *line)
{
	int	i;
	int	len;
	int	line_len;

	line_len = ft_strlen(line);
	i = 0;
	while (line[i])
	{
		len = skip_quote_with_pipe(&line[i]);
		if (len > 0)
		{
			line[i + len] = '\0';
			add_process(process, ft_strdup(&line[i]));
			i += len;
		}
		if (i != line_len)
			i++;
	}
}	

void	tokenize(t_process **process, t_env **env, char *line, char **envp)
{
	t_process	*cur;

	create_env_list(env, envp);
	split_process(process, line);
	cur = *process;
	while (cur)
	{
		parse_redir(cur);
		parse_cmd(cur);
		replace_process_resources(cur, env);
		cur = cur->next;
	}
}
