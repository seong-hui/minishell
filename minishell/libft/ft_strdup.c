/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:36:37 by jooypark          #+#    #+#             */
/*   Updated: 2023/11/06 20:54:26 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*copy;
	int		s_len;
	int		i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	copy = (char *)malloc((s_len + 1) * sizeof(char));
	if (!copy)
		return (0);
	i = 0;
	while (i <= s_len)
	{
		copy[i] = s[i];
		i++;
	}
	return (copy);
}
