/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:30:44 by moonseonghu       #+#    #+#             */
/*   Updated: 2023/11/07 17:02:25 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

unsigned long long	ft_atoi_cal(char *str, int *flag, int sign)
{
	unsigned long long	re;
	int					i;

	re = 0;
	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			re = re * 10 + (str[i] - '0');
			if (sign == 1 && re > 9223372036854775807)
				*flag = 1;
			else if (sign == -1 && re - 1 > 9223372036854775807)
				*flag = 1;
		}
		else
		{
			*flag = 1;
			break ;
		}
		i++;
	}
	return (re);
}

int	ft_atoi_for_exit(char *str, int *flag)
{
	int					i;
	int					sign;
	unsigned long long	re;

	i = 0;
	sign = 1;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	re = ft_atoi_cal(str + i, flag, sign);
	return ((int)re * sign);
}

void	builtin_exit(t_process *process, t_excute e_info)
{
	int	cmd_len;
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	cmd_len = ft_cmdsize(process->cmd);
	g_exit_code = 0;
	if (cmd_len == 1 && e_info.cmd_size == 1)
	{
		ft_putstr_fd("exit\n", 2);
		exit(g_exit_code);
	}
	if (e_info.cmd_size == 1)
		ft_putstr_fd("exit\n", 2);
	g_exit_code = (unsigned char)ft_atoi_for_exit(process->cmd[1], &flag);
	if (flag)
		print_exit_error1(process->cmd[1]);
	else if (cmd_len > 2)
		print_exit_error2();
	exit(g_exit_code);
}
