/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:26:42 by moonseonghu       #+#    #+#             */
/*   Updated: 2023/10/31 17:44:13 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "parse.h"

void	check_builtins(t_process *process, t_env *env, int fd);
int		is_builtin(t_process *process);
int		ft_lstsize(t_process *lst);
void	check_heredoc(t_process *process);
void fd_redirection(t_process *process, t_redir *redir);
void make_pipe(t_process *process, int cmd_size, char **execute_path, t_env *env, char **envp);
char *get_cmd(char **path, char *cmd);
char **get_path(t_env *env);
void first_child(t_process *process, int *cur_fd, t_env *env, char *cmd, char **envp);
void middle_child(t_process *process, int *prev_fd, int *cur_fd, t_env *env, char *cmd, char **envp);
void last_child(t_process *process, int *prev_fd, t_env *env, char *cmd, char **envp);
//ßvoid	wait_process(int pid);
void	exit_code_handler(int status, int *flag_printed, int pid, int child);

#endif