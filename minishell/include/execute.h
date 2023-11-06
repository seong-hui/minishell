/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:26:42 by moonseonghu       #+#    #+#             */
/*   Updated: 2023/11/06 20:48:27 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <unistd.h>
# include <sys/wait.h>
# include "parse.h"

typedef struct s_execute
{
	int				cmd_size;
	char			**envp;
	char			**execute_path;
	int				prev_fd[2];
	int				i;
}	t_excute;

void	check_builtins(t_process *process, t_env *env, int fd, t_excute e_info);
int		is_builtin(t_process *process);
int		ft_lstsize(t_process *lst);
void	check_heredoc(t_process *process);
void	fd_redirection(t_process *process, t_redir *redir);
void	make_pipe(t_process *process, t_env *env, t_excute exe_info);
char	*get_cmd(char **path, char *cmd);
char	**get_path(t_env *env);
void	first_child(t_process *proc, int *cur_fd, t_env *env, t_excute e_info);
void	middle_child(t_process *proc, int *cur_fd, t_env *env, t_excute e_info);
void	last_child(t_process *process, t_env *env, t_excute e_info);
void	exit_code_handler(int status, int *flag_printed, int pid, int child);
void	print_file_error(char *file);
void	print_command_error(char *cmd);
void	wait_child(int i, int exit_code);
int		child_exit_status(int exit_code);

#endif