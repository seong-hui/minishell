/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:33:16 by moonseonghu       #+#    #+#             */
/*   Updated: 2023/10/23 15:32:54 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void builtin_env(t_process *process, t_env *env, int fd)
{
    t_env *start;

    start = env;
    while(env)
    {
         ft_putstr_fd(env->key, fd);
         ft_putstr_fd("=", fd);
         ft_putendl_fd(env->value, fd);
        env = env->next;
    }
    env = start;
    return;
}
