/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:46:12 by jooypark          #+#    #+#             */
/*   Updated: 2023/04/09 18:36:06 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	sub_len;
	size_t	i;

	s_len = ft_strlen(s);
	if (start > s_len)
		sub_len = 0;
	else if (s_len < len + start)
		sub_len = s_len - start;
	else
		sub_len = len;
	sub = (char *)malloc((sub_len + 1) * sizeof(char));
	if (!sub)
		return (0);
	i = 0;
	while (i < sub_len)
	{
		sub[i] = s[start + (unsigned int)i];
		i++;
	}
	sub[i] = 0;
	return (sub);
}
