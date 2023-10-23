/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:41:14 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/11 17:39:16 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	count_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	count_word(char const*s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != '\0')
			cnt++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (cnt);
}

char	*put_str(char const*s, char c, int *index)
{
	int		i;
	char	*pp;
	int		cnt_len;

	i = 0;
	while (s[*index] && s[*index] == c)
		*index += 1;
	cnt_len = count_len(s + *index, c);
	pp = (char *)malloc(cnt_len + 1);
	if (!pp)
		return (0);
	while (s[*index] && s[*index] != c)
	{
		pp[i] = s[*index];
		*index += 1;
		i++;
	}
	pp[i] = '\0';
	return (pp);
}

char	**ft_split(char const *s, char c)
{
	int		cnt_word;
	char	**p;
	int		i;
	int		index;

	cnt_word = count_word(s, c);
	p = (char **)malloc(sizeof(char *) * (cnt_word + 1));
	if (!p)
		return (0);
	i = 0;
	index = 0;
	while (i < cnt_word)
	{
		p[i] = put_str(s, c, &index);
		if (!p[i])
		{
			while (--i >= 0)
				free (p[i]);
			free(p);
			return (0);
		}
		i++;
	}
	p[cnt_word] = 0;
	return (p);
}
