/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:15:31 by jooypark          #+#    #+#             */
/*   Updated: 2023/04/09 18:35:34 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	idx;
	size_t	i;

	needle_len = (size_t)ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	idx = 0;
	while (haystack[idx] && idx + needle_len <= len)
	{
		if (haystack[idx] == needle[0])
		{
			i = 0;
			while (i < needle_len)
			{
				if (haystack[idx + i] != needle[i])
					break ;
				i++;
			}
			if (i == needle_len)
				return ((char *)&haystack[idx]);
		}
		idx++;
	}
	return (0);
}
