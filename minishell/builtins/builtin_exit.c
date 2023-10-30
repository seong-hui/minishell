/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:30:44 by moonseonghu       #+#    #+#             */
/*   Updated: 2023/10/29 21:06:55 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int ft_cmdsize(char **cmd)
{
    int len;

    len = 0;
    while (cmd[len])
    {
        len++;
    }
    return (len);
}

int ft_atoi_for_exit(char *str, int *flag)
{
    int i;
    int sign;
    unsigned long long re;

    i = 0;
    sign = 1;
    re = 0;
    while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i])
    {
        if (ft_isdigit(str[i]))
        {
            re = re * 10 + (str[i] - '0');
            if (sign == 1 && re > 9223372036854775807)
                *flag = 1;
            else if (sign == -1 && re > 9223372036854775807 + 1)
                *flag = 1;
        }
        else
        {
            *flag = 1;
            break;
        }
        i++;
    }
    return ((int)re * sign);
}

void builtin_exit(t_process *process)
{
    int cmd_len;
    int i;
    int flag;

    i = 0;
    flag = 0;
    cmd_len = ft_cmdsize(process->cmd);
    g_exit_code = 0;
    if (cmd_len == 1)
    {
        write(1, "exit\n", 5);
        exit(g_exit_code);
    }
    write(1, "exit\n", 5);
    g_exit_code = (unsigned char)ft_atoi_for_exit(process->cmd[1], &flag);
    if (flag)
    {
        write(2, "exit: ", ft_strlen("exit: "));
        write(2, process->cmd[1], ft_strlen(process->cmd[1]));
        write(2, ": numeric argument required\n", ft_strlen(": numeric argument required\n"));
        g_exit_code = 255;
    }
    else if (cmd_len > 2)
    {
        write(2, "exit: too many argument\n", ft_strlen("exit: too many argument\n"));
        g_exit_code = 1;
    }
    // printf("[%d]\n", g_exit_code);
    exit(g_exit_code);
}
