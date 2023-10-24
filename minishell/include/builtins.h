/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:35:59 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/24 20:40:01 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
#include "parse.h"

void	builtin_echo(t_process *process, int fd);
void builtin_pwd(void);
void builtin_cd(t_process *process);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
void	check_builtins(t_process *process, t_env *env, int fd);
void process_start(t_process *process, t_env *env, char **envp);
void builtin_env(t_process *process, t_env *env, int fd);
void fd_redirection(t_process *process, t_redir *redir);
void	builtin_export(t_process *process, t_env *env, int fd);
void builtin_env(t_process *process, t_env *env, int fd);
void builtin_unset(t_process *process, t_env *env, int fd);

#endif

