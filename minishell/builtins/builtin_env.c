/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:33:16 by moonseonghu       #+#    #+#             */
/*   Updated: 2023/10/24 20:51:11 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void builtin_env(t_process *process, t_env *env, int fd)
{

    while (env)
    {
         ft_putstr_fd(env->key, fd);
         ft_putstr_fd("=", fd);
         ft_putendl_fd(env->value, fd);
        env = env->next;
    }
}
