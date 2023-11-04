#include "../include/parse.h"

int	count_not_empty(char **cmd)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i][0] != '\0')
			cnt++;
		i++;
	}
	return (cnt);
}

char	**remove_empty_cmd(char **cmd)
{
	int		i;
	int		j;
	int		count;
	char	**new_cmd;

	count = count_not_empty(cmd);
	if (count == 0)
		return (NULL);
	new_cmd = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i][0] != '\0')
			new_cmd[j++] = ft_strdup(cmd[i]);
		free(cmd[i++]);
	}
	new_cmd[j] = NULL;
	free(cmd);
	return (new_cmd);
}

void	remove_empty_process(t_process **process)
{
	t_process	*prev;
	t_process	*cur;

	prev = NULL;
	cur = *process;
	while (cur)
	{
		if (cur->cmd == NULL && cur->redir == NULL)
		{
			if (prev == NULL)
			{
				*process = cur->next;
				free(cur);
				cur = *process;
			}
			else
			{
				prev->next = cur->next;
				free(cur);
				cur = prev->next;
			}
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

void	remove_empty(t_process **process)
{
	t_process	*pre;
	t_process	*cur;

	pre = NULL;
	cur = *process;
	while (cur)
	{
		cur->cmd = remove_empty_cmd(cur->cmd);
		cur = cur->next;
	}
	remove_empty_process(process);
}
