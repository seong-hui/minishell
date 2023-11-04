/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/11/04 16:26:37 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "parse.h"
#include "execute.h"

void builtin_echo(t_process *process, int fd);
void builtin_pwd(int fd);
void builtin_cd(t_process *process);
char *ft_strncpy(char *dest, char *src, unsigned int n);
void	no_fork_toexecute(t_process *process, t_env *env, t_excute e_info);
void process_start(t_process *process, t_env *env, char **envp);
void builtin_env(t_process *process, t_env *env, int fd);
void fd_redirection(t_process *process, t_redir *redir);
void	builtin_export(t_process *process, t_env *env, int fd, t_excute e_info);
void builtin_env(t_process *process, t_env *env, int fd);
void builtin_unset(t_process *process, t_env *env, int fd);
void builtin_exit(t_process *process);
char *get_path_key(char *envp);
char *get_path_value(char *envp);
void	print_exit_error1(char *file);
void	print_exit_error2(void);
void	print_export_error(char *file);
int	ft_cmdsize(char **cmd);
t_env	*sort_list(t_env *env);
void	check_value(char *env_str);
int	search_env_key(t_env **env, char *search);
void	print_unset_error(char *file);

#endif
