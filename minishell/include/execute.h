/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:26:42 by moonseonghu       #+#    #+#             */
/*   Updated: 2023/10/24 14:41:14 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
#include "parse.h"

// char	**ft_split(char const *s, char c);
// void	builtin_echo(t_process *process);
// void builtin_pwd(t_process *process);
// void builtin_cd(t_process *process);
// char	*ft_strncpy(char *dest, char *src, unsigned int n);
// void	check_biltins(t_process *process);
// void process_start(t_process *process, char **env);
void	check_builtins(t_process *process, t_env *env, int fd);
int is_builtin(t_process *process);

#endif