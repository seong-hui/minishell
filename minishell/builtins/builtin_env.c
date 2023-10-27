/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:33:16 by moonseonghu       #+#    #+#             */
/*   Updated: 2023/10/25 22:13:38 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void builtin_env(t_process *process, t_env *env, int fd)
{

    while (env)
    {
         ft_putstr_fd(env->key, fd);
         if (env->value)
         {
            ft_putstr_fd("=", fd);
            ft_putstr_fd(env->value, fd);
         }
         ft_putstr_fd("\n", fd);
        env = env->next;
    }
}
