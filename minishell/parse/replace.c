/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:43:31 by jooypark          #+#    #+#             */
/*   Updated: 2023/11/05 20:43:32 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

int	replace_len(char *str, t_env **env)
{
	int		len;
	int		quote;
	char	*env_key;

	len = 0;
	quote = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			update_quote(*str, &quote);
		else if (*str == '$' && quote != '\'')
		{
			env_key = get_env_key(str + 1);
			if ((ft_strlen(env_key) == 0) && (quote != 0
					|| !(*(str + 1) == '\'' || *(str + 1) == '"')))
				len++;
			else
				str += expand_len(&len, str, env, quote);
		}
		else
			len++;
		str++;
	}
	return (len);
}

char	*replace_str(char *str, t_env **env)
{
	char		*env_key;
	char		*replaced;
	t_expand	expand;

	init_expand(&expand, str, env);
	replaced = (char *)malloc(sizeof(char) * (expand.len + 1));
	while (expand.idx < expand.len)
	{
		if (*expand.cmd == '\'' || *expand.cmd == '"')
			update_quote(*expand.cmd, &expand.quote);
		else if (*expand.cmd == '$' && expand.quote != '\'')
			expand_cmd(replaced, &expand, env);
		else
			replaced[expand.idx++] = *expand.cmd;
		expand.cmd++;
	}
	replaced[expand.idx] = 0;
	return (replaced);
}

char	*replace_limiter(char *file)
{
	int		i;
	int		quote;
	char	*replaced;

	i = 0;
	quote = 0;
	replaced = (char *)malloc(sizeof(char) * (ft_strlen(file) + 1));
	while (*file)
	{
		if (*file == '\'' || *file == '"')
			update_quote(*file, &quote);
		else if (*file == '$')
		{
			if (quote != 0 || !(*(file + 1) == '\'' || *(file + 1) == '"'))
				replaced[i++] = *file;
		}
		else
			replaced[i++] = *file;
		file++;
	}
	replaced[i] = '\0';
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
