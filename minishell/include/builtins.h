/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:29:13 by moonseonghu       #+#    #+#             */
/*   Updated: 2023/11/05 20:08:59 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "parse.h"
# include "execute.h"

void	builtin_echo(t_process *process, int fd);
void	builtin_pwd(int fd, t_env *env);
void	builtin_cd(t_process *process, t_env *env);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
void	no_fork_toexecute(t_process *process, t_env *env, t_excute e_info);
void	process_start(t_process *process, t_env *env, char **envp);
void	builtin_env(t_process *process, t_env *env, int fd);
void	fd_redirection(t_process *process, t_redir *redir);
void	builtin_export(t_process *process, t_env *env, int fd, t_excute e_info);
void	builtin_env(t_process *process, t_env *env, int fd);
void	builtin_unset(t_process *process, t_env *env, int fd);
void	builtin_exit(t_process *process);
char	*get_path_key(char *envp);
char	*get_path_value(char *envp);
void	print_exit_error1(char *file);
void	print_exit_error2(void);
void	print_export_error(char *file);
int		ft_cmdsize(char **cmd);
t_env	*sort_list(t_env *env);
void	check_value(char *env_str);
int		search_env_key(t_env **env, char *search);
void	print_unset_error(char *file);
void	replace_env(t_env **env, char *key, char *value);
char	*search_env_value(t_env **env, char *search);
t_env	*copy_env(t_env *env);
void	replace_env_value(t_env **env, char *key, char *value, int equl);
void	copy_key_value(t_env *env, t_env *new_env);
void	print_pwd_error(char *file);
void	print_cd_error(char *file);

#endif
