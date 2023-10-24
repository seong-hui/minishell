/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:35:59 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/24 21:03:34 by jooypark         ###   ########seoul.kr  */
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

char	**ft_split(char const *s, char c);
void	builtin_echo(t_process *process, int fd);
void builtin_pwd(void);
void builtin_cd(t_process *process);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
void	check_builtins(t_process *process, t_env *env, int fd);
void process_start(t_process *process, t_env *env, char **envp);
void builtin_env(t_process *process, t_env *env, int fd);
void fd_redirection(t_process *process, t_redir *redir);

#endif

