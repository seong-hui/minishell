/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:52:25 by moonseonghu       #+#    #+#             */
/*   Updated: 2023/10/16 04:32:32 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"


int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(char *s1)
{
	char	*p;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	p = (char *)malloc(len + 1);
	if (!p)
		return (0);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len1;
	int		len2;
	char	*p;
	int		i;
	int		j;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	p = (char *)malloc(len1 + len2 + 1);
	if (!p)
		return (0);
	i = 0;
	while (i < len1)
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (i < len1 + len2)
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}

void	exit_error(void)
{
	perror(NULL);
	exit(1);
}
