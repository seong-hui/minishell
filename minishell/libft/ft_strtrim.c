/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:36:18 by jooypark          #+#    #+#             */
/*   Updated: 2023/10/11 20:14:41 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

int	get_copy_len(char const *s1, char const *set)
{
	int		end;

	if (!*s1)
		return (0);
	end = 0;
	while (s1[end])
		end++;
	end -= 1;
	while (check_set(s1[end], set))
		end--;
	return (end + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*copy;
	int		copy_len;
	int		i;

	while (check_set(*s1, set))
		s1++;
	copy_len = get_copy_len(s1, set);
	copy = (char *)malloc((copy_len + 1) * sizeof(char));
	if (!copy)
		return (0);
	i = 0;
	while (i < copy_len)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = 0;
	return (copy);
}
