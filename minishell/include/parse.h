/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/11/06 17:37:17 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSE_H
# define PARSE_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <signal.h>
# include <termios.h>

# define T_SIMPLE 0
# define T_PIPE 1
# define T_REDIR_INPUT 2
# define T_REDIR_OUTPUT 3
# define T_REDIR_HEREDOC 4
# define T_REDIR_APPEND 5

int	g_exit_code;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
	char			*tmp;
}	t_redir;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	int				equal_sign;
}	t_env;

typedef struct s_process
{
	t_redir         *redir;
	char            **cmd;
	struct s_process  *next;
	int             infile_fd;
	int             outfile_fd;
	char			*cmd_line;
	char            *cmd_path;
}   t_process;

typedef struct s_expand
{
	char	*cmd;
	int		len;
	int		idx;
	int		quote;
}	t_expand;


int tokenize(t_process **process, t_env **env, char *line);
void    parse_redir(t_process *process);
void    parse_cmd(t_process *process);
char    *ft_strndup(const char *s, int n);
int     ft_strcmp(const char *s1, const char *s2);
void    create_env_list(t_env **env, char **envp);
void    replace_process_resources(t_process *process, t_env **env);
char    *search_env_value(t_env **env, char *search);
int    check_syntax(t_process **process);
void    free_redir_list(t_redir *redir);
void	free_process(t_process *process);
void    free_process_list(t_process **process);
void    free_env(t_env *env);
void    free_env_list(t_env *env);
int in_charset(char c, char *charset);
void    print_syntax_error(char *str);
void    print_file_error(char *file);
void    detect_signal(void);
void    signal_handler(int signo);
void    set_terminal_print_off(void);
void    set_terminal_print_on(void);
void process_start(t_process *process, t_env *env, char **envp);
void	add_env(t_env **env, char *key, char *value, int equl);
void	delete_env(t_env **env, char *del_key);
char	*search_env_value(t_env **env, char *search);
char	*get_env_key(char *str);
void	set_terminal_print_off(void);

void	remove_empty(t_process **process);
int	is_all_blank(char *line);
void	trim_spaces(t_process *process);

void all_signal();
void	exec_signal(int signo);

int	replace_len(char *str, t_env **env);
char	*replace_str(char *str, t_env **env);
char	*replace_limiter(char *file);
char	*replace_redir_file(char *file, int type, t_env **env);
void	replace_process_resources(t_process *process, t_env **env);

void	update_quote(char c, int *quote);
int	expand_len(int *len, char *str, t_env **env, int quote);
void	expand_cmd(char *replaced, t_expand *expand, t_env **env);
void	init_expand(t_expand *expand, char *str, t_env **env);

void	main_sigint_handler(int sign);
#endif