/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:57:59 by jooypark          #+#    #+#             */
/*   Updated: 2023/04/09 18:35:16 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*result;
	unsigned int		s_len;
	unsigned int		idx;

	s_len = ft_strlen(s);
	result = (char *)malloc((s_len + 1) * sizeof(char));
	if (!result)
		return (0);
	idx = 0;
	while (idx < s_len)
	{
		result[idx] = (*f)(idx, s[idx]);
		idx++;
	}
	result[idx] = 0;
	return (result);
}
