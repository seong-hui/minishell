/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:53:37 by jooypark          #+#    #+#             */
/*   Updated: 2023/04/09 18:34:18 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	s_len;
	int		i;

	s_len = ft_strlen(s1) + ft_strlen(s2);
	s = (char *)malloc((s_len + 1) * sizeof(char));
	if (!s)
		return (0);
	i = 0;
	while (*s1)
	{
		s[i++] = *s1;
		s1++;
	}
	while (*s2)
	{
		s[i++] = *s2;
		s2++;
	}
	s[i] = 0;
	return (s);
}
