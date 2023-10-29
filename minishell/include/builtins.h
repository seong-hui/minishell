/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/26 17:25:33 by moonseonghu      ###   ########.fr       */
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
#include "execute.h"

void	builtin_echo(t_process *process, int fd);
void builtin_pwd(void);
void builtin_cd(t_process *process);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
void	check_builtins(t_process *process, t_env *env, int fd, int is_single);
void process_start(t_process *process, t_env *env, char **envp);
void builtin_env(t_process *process, t_env *env, int fd);
void fd_redirection(t_process *process, t_redir *redir);
void	builtin_export(t_process *process, t_env *env, int fd);
void builtin_env(t_process *process, t_env *env, int fd);
void builtin_unset(t_process *process, t_env *env, int fd);
void builtin_exit(t_process *process);
char	*get_path_key(char *envp);
char	*get_path_value(char *envp);

#endif

