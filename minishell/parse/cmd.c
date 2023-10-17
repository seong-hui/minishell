
#include "../include/parse.h"


int	count_cmd(char *line)
{
	int	quote;
	int	i;
	int	count;

	i = 0;
	quote = 0;
	count = 0;
	while (line[i])
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\n' || line[i] == '\t'))
			i++;
		if (line[i] && !(line[i] == ' ' || line[i] == '\n' || line[i] == '\t'))
			count++;
		while (line[i] && !(line[i] == ' ' || line[i] == '\n' || line[i] == '\t'))
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
	int	i;
	int	len;
	int	quote;
	char	*new_cmd;

	len = 0;
	while (line[len] && !(line[len] == ' ' || line[len] == '\n' || line[len] == '\t'))
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
	//printf("len: %d, new_cmd: %s\n", len, new_cmd);
	return (new_cmd);
}

void	parse_cmd(t_process *process)
{
	int	i;
	int	j;
	int	quote;
	char **cmd_arr;
	int	cmd_cnt;

	cmd_cnt = count_cmd(process->cmd_line);
	//printf("%s, %d\n", process->cmd_line, cmd_cnt);
	cmd_arr = (char **)malloc(sizeof(char *) * (cmd_cnt + 1));
	i = 0;
	j = 0;
	while (j < cmd_cnt)
	{
		while (process->cmd_line[i] && (process->cmd_line[i] == ' ' || process->cmd_line[i] == '\n'
				|| process->cmd_line[i] == '\t'))
			i++;
		if (process->cmd_line[i])
			cmd_arr[j++] = add_new_cmd(&process->cmd_line[i]);
		while (process->cmd_line[i] && !(process->cmd_line[i] == ' ' || process->cmd_line[i] == '\n'
				|| process->cmd_line[i] == '\t'))
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
