/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:21:15 by jooypark          #+#    #+#             */
/*   Updated: 2023/04/09 19:43:59 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptr_d;
	unsigned char	*ptr_s;

	if (!dst && !src)
		return (0);
	i = 0;
	ptr_d = (unsigned char *)dst;
	ptr_s = (unsigned char *)src;
	if (ptr_d < ptr_s)
	{
		while (i < n)
		{
			ptr_d[i] = ptr_s[i];
			i++;
		}
	}
	else
	{
		while (++i <= n)
			ptr_d[n - i] = ptr_s[n - i];
	}
	return ((void *)dst);
}
