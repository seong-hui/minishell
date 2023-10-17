/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:41:46 by jooypark          #+#    #+#             */
/*   Updated: 2023/10/09 17:11:40 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_word(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

char	*put_word(char const *s, char c)
{
	char	*word;
	int		word_len;
	int		i;

	word_len = 0;
	while (s[word_len] && s[word_len] != c)
		word_len++;
	word = (char *)malloc((word_len + 1) * sizeof(char));
	if (!word)
		return (0);
	i = 0;
	while (s[i] != c && s[i])
	{
		word[i] = s[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

char	**ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		count;
	int		i;

	count = count_word(s, c);
	words = (char **)malloc(sizeof(char *) * (count + 1));
	if (!words)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			words[i] = put_word(s, c);
			if (words[i] == 0)
				return (ft_free(words));
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	words[i] = 0;
	return (words);
}
