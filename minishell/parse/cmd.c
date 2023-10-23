
#include "../include/parse.h"


int	count_cmd(char *line)
{
	int	i;
	int	quote;
	int	count;

	i = 0;
	quote = 0;
	count = 0;
	while (line[i])
	{
		while (line[i] && in_charset(line[i], " \n\t"))
			i++;
		if (line[i] && !in_charset(line[i], " \n\t"))
			count++;
		while (line[i] && !in_charset(line[i], " \n\t"))
		{
			if (line[i] == '\'' || line[i] == '"')
			{
				quote = line[i++];
				while (quote != line[i])
					i++;
			}
			i++;
		}
	}
	return (count);
}

char	*add_new_cmd(char *line)
{
	int		i;
	int		len;
	int		quote;
	char	*new_cmd;

	len = 0;
	while (line[len] && !in_charset(line[len], " \n\t"))
	{
		if (line[len] == '\'' || line[len] == '"')
		{
			quote = line[len++];
			while (quote != line[len])
				len++;
		}
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
	int		i;
	int		j;
	int		quote;
	char	**cmd_arr;
	int		cmd_cnt;

	cmd_cnt = count_cmd(process->cmd_line);
	cmd_arr = (char **)malloc(sizeof(char *) * (cmd_cnt + 1));
	i = 0;
	j = 0;
	while (j < cmd_cnt)
	{
		while (in_charset(process->cmd_line[i], " \n\t"))
			i++;
		if (process->cmd_line[i])
			cmd_arr[j++] = add_new_cmd(&process->cmd_line[i]);
		while (process->cmd_line[i] && !in_charset(process->cmd_line[i], " \n\t"))
		{
			if (process->cmd_line[i] == '\'' || process->cmd_line[i] == '"')
			{
				quote = process->cmd_line[i++];
				while (quote != process->cmd_line[i])
					i++;
			}
			i++;
		}
	}
	cmd_arr[j] = NULL;
	process->cmd = cmd_arr;
}
