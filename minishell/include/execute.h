/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:26:42 by moonseonghu       #+#    #+#             */
/*   Updated: 2023/11/15 17:07:12 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "parse.h"

typedef struct s_execute
{
	int		cmd_size;
	char	**envp;
	char	**execute_path;
	int		prev_fd[2];
	int		i;
	int		exe_flag;
}	t_excute;

typedef struct s_here
{
	int		i;
	pid_t	pid;
}	t_here;

void	check_builtins(t_process *proc, t_env **env, int fd, t_excute e_info);
int		is_builtin(t_process *process);
int		ft_lstsize(t_process *lst);
void	check_heredoc(t_process *process, t_env *env);
int		fd_redirection(t_process *process, t_redir *redir);
void	make_pipe(t_process *process, t_env **env, t_excute exe_info);
char	*get_cmd(char **path, char *cmd);
char	**get_path(t_env *env);
void	first_child(t_process *proc, int *fd, t_env **env, t_excute e_info);
void	middle_child(t_process *proc, int *fd, t_env **env, t_excute e_info);
void	last_child(t_process *process, t_env **env, t_excute e_info);
void	exit_code_handler(int status, int *flag_printed, int pid, int child);
void	print_file_error(char *file);
void	wait_child(int i, int exit_code);
int		child_exit_status(int exit_code);
void	unlink_file(t_redir *redir);
char	**copy_envp(char **envp);
void	exit_and_setcode(void);
void	close_fd(t_process *process);
void	handle_heredoc(t_redir *redir, t_process *proc, t_here *he, t_env *env);
void	child_process(t_process *proc, t_env **env, t_excute info, int *cur_fd);
void	evecve_error(char *cmd);
void	util_write(char *str);

#endif