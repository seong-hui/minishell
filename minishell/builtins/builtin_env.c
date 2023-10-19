/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:33:16 by moonseonghu       #+#    #+#             */
/*   Updated: 2023/10/19 21:46:31 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void builtin_env(t_process *process, t_env *env)
{
    while(env)
    {
        printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
}
