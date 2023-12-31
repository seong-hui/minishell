/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 22:18:50 by jooypark          #+#    #+#             */
/*   Updated: 2023/11/14 22:13:14 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	in_charset(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

char	*ft_strndup(const char *s, int n)
{
	char	*copy;
	int		i;

	copy = (char *)malloc((n + 1) * sizeof(char));
	if (!copy)
		return (0);
	i = 0;
	while (i < n)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = 0;
	return (copy);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

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
