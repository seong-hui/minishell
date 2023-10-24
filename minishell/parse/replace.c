
#include "../include/parse.h"


void	trim_spaces(t_process *process)
{
	int		i;
	char	*trimmed;
	t_redir	*cur_redir;

	if (!process->cmd)
		return ;
	i = 0;
	while (process->cmd[i])
	{
		trimmed = ft_strtrim(process->cmd[i], " \n\t");
		free(process->cmd[i]);
		process->cmd[i] = trimmed;
		i++;
	}
	if (!process->redir)
		return ;
	cur_redir = process->redir;
	while (cur_redir)
	{
		trimmed = ft_strtrim(cur_redir->file, " \n\t");
		free(cur_redir->file);
		cur_redir->file = trimmed;
		cur_redir = cur_redir->next;
	}
}

char	*get_env_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		if (i == 0 && ft_isdigit(str[i]))
		{
			i = 1;
			break ;
		}
		i++;
	}
	key = ft_strndup(str, i);
	return (key);
}

int	count_replace_str_len(char *str, t_env **env)
{
	int		i;
	int		len;
	char	*env_key;
	char	*env_value;
	int		quote;

	i = 0;
	len = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == 0)
			quote = str[i];
		else if ((str[i] == '\'' || str[i] == '"') && quote == str[i])
			quote = 0;
		else if (str[i] == '$' && quote != '\'')
		{
			env_key = get_env_key(&str[i + 1]);
			if ((ft_strlen(env_key) == 0) && (quote != 0
					|| !(str[i + 1] == '\'' || str[i + 1] == '"')))
				len++;
			else
			{
				env_value = search_env_value(env, env_key);
				if (env_value != NULL)
					len += ft_strlen(env_value);
				i += ft_strlen(env_key);
			}
			free(env_key);
		}
		else
			len++;
		i++;
	}
	return (len);
}

char	*replace_str(char *str, t_env **env)
{
	int		i;
	int		j;
	int		len;
	char	*env_key;
	char	*env_value;
	int		quote;
	char	*replaced;

	len = count_replace_str_len(str, env);
	replaced = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	j = 0;
	quote = 0;
	while (j < len)
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == 0)
			quote = str[i];
		else if ((str[i] == '\'' || str[i] == '"') && quote == str[i])
			quote = 0;
		else if (str[i] == '$' && quote != '\'')
		{
			env_key = get_env_key(&str[i + 1]);
			if ((ft_strlen(env_key) == 0) && (quote != 0
					|| !(str[i + 1] == '\'' || str[i + 1] == '"')))
				replaced[j++] = '$';
			else
			{
				env_value = search_env_value(env, env_key);
				//printf("%s\n", env_value);
				if (env_value != NULL)
				{
					while (*env_value)
						replaced[j++] = *env_value++;
				}
				i += ft_strlen(env_key);
			}
			free(env_key);
		}
		else
			replaced[j++] = str[i];
		i++;
	}
	replaced[j] = 0;
	return (replaced);
}

char	*replace_limiter(char *file)
{
	int	i;
	int	j;
	int	quote;
	char	*replaced;

	i = 0;
	j = 0;
	quote = 0;
	replaced = (char *)malloc(sizeof(char) * (ft_strlen(file) + 1));
	while (file[i])
	{
		if ((file[i] == '\'' || file[i] == '"'))
		{
			if (quote == 0)
				quote = file[i];
			else if (file[i] == quote)
				quote = 0;
		}
		else if (file[i] == '$')
		{
			if (quote != 0 || !(file[i + 1] == '\'' || file[i + 1] == '"'))
				replaced[j++] = file[i];
		}
		else
			replaced[j++] = file[i];
		i++;
	}
	replaced[j] = '\0';
	return (replaced);
}

char	*replace_redir_file(char *file, int type, t_env **env)
{
	int		i;
	int		is_dollar;
	char	*replaced;

	if (type != T_REDIR_HEREDOC)
		replaced = replace_str(file, env);
	else
	{
		i = 0;
		is_dollar = 0;
		while (file[i])
		{
			if (file[i] == '$')
				is_dollar = 1;
			i++;
		}
		if (is_dollar == 0)
			replaced = replace_str(file, env);
		else
			replaced = replace_limiter(file);
	}
	return (replaced);
}

void	replace_process_resources(t_process *process, t_env **env)
{
	int		i;
	char	*replaced;
	t_redir	*cur_redir;

	trim_spaces(process);
	if (!process->cmd)
		return ;
	i = 0;
	while (process->cmd[i])
	{
		replaced = replace_str(process->cmd[i], env);
		free(process->cmd[i]);
		process->cmd[i] = replaced;
		i++;
	}
	if (!process->redir)
		return ;
	cur_redir = process->redir;
	while (cur_redir)
	{
		replaced = replace_redir_file(cur_redir->file, cur_redir->type, env);
		free(cur_redir->file);
		cur_redir->file = replaced;
		cur_redir = cur_redir->next;
	}
}
