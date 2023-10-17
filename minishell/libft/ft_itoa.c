/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:34:37 by jooypark          #+#    #+#             */
/*   Updated: 2023/05/15 17:23:26 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_len(long long num)
{
	int	len;

	if (num == 0)
		return (1);
	len = 0;
	if (num < 0)
	{
		num *= -1;
		len++;
	}
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*n_str;
	long long	num;
	int			n_str_len;

	num = n;
	n_str_len = get_len(num);
	n_str = (char *)malloc((n_str_len + 1) * sizeof(char));
	if (!n_str)
		return (0);
	if (num < 0)
	{
		n_str[0] = '-';
		num *= -1;
	}
	n_str[n_str_len--] = 0;
	if (num == 0)
		n_str[0] = '0';
	while (num > 0)
	{
		n_str[n_str_len--] = '0' + (num % 10);
		num /= 10;
	}
	return (n_str);
}
