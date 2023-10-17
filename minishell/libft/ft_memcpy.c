/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:14:16 by jooypark          #+#    #+#             */
/*   Updated: 2023/04/09 18:32:11 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*ptr_d;
	unsigned char		*ptr_s;

	i = 0;
	ptr_d = (unsigned char *)dst;
	ptr_s = (unsigned char *)src;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		ptr_d[i] = ptr_s[i];
		i++;
	}
	return ((void *)dst);
}
