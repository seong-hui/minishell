/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:09:19 by jooypark          #+#    #+#             */
/*   Updated: 2023/11/07 20:09:27 by seonghmo         ###   ########.fr       */
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
	t_redir				*redir;
	char				**cmd;
	struct s_process	*next;
	int					infile_fd;
	int					outfile_fd;
	char				*cmd_line;
	char				*cmd_path;
}	t_process;

typedef struct s_expand
{
	char	*cmd;
	int		len;
	int		idx;
	int		quote;
}	t_expand;

// main.c
void	run_prompt(t_env *env, char **envp);

// utils.c
int		in_charset(char c, char *charset);
char	*ft_strndup(const char *s, int n);
int		ft_strcmp(const char *s1, const char *s2);
void	trim_spaces(t_process *process);

// tokenize.c
int		is_all_blank(char *line);
int		is_quote_closed(char *line);
int		tokenize(t_process **process, t_env **env, char *line);

// pipe.c
void	add_process(t_process **process, char *cmd_line);
int		skip_quote_with_pipe(char *line);
int		split_process(t_process **process, char *line);
void	handle_signal(void);

// redirection.c
void	add_redir(t_redir **redir, char *file, int type);
int		is_redir(char *line);
int		get_file_len(char *line);
int		get_file_loc(char *line, int type);
void	parse_redir(t_process *process);

// cmd.c
int		skip_quote(char *line);
int		count_cmd(char *line);
char	*add_new_cmd(char *line);
void	parse_cmd(t_process *process);

// env.c
void	add_env(t_env **env, char *key, char *value, int equal);
void	delete_env(t_env **env, char *del_key);
char	*get_env_key(char *str);
char	*search_env_value(t_env **env, char *search);
void	create_env_list(t_env **env, char **envp);

// path.c
char	*get_path_value(char *envp);
char	*get_path_key(char *envp);

// replace.c
int		replace_len(char *str, t_env **env);
char	*replace_str(char *str, t_env **env);
char	*replace_limiter(char *file);
char	*replace_redir_file(char *file, int type, t_env **env);
void	replace_process_resources(t_process *process, t_env **env);

// expand.c
void	init_expand(t_expand *expand, char *str, t_env **env);
int		expand_len(int *len, char *str, t_env **env, int quote);
void	expand_cmd(char *replaced, t_expand *expand, t_env **env);

// syntax.c
void	print_syntax_error(char *str);
int		check_syntax(t_process **process);

// signal.c
void	signal_handler(int signo);
void	exec_signal(int signo);
void	heredoc_signal(int signo);
void	detect_signal(void);

// terminal.c
void	set_terminal_print_off(void);
void	set_terminal_print_on(void);

// free.c
void	free_redir_list(t_redir *redir);
void	free_process(t_process *process);
void	free_process_list(t_process **process);
void	free_env(t_env *env);
void	free_env_list(t_env *env);

#endif