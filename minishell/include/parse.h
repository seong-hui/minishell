/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/11/02 16:58:22 by seonghmo         ###   ########.fr       */
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
    char            *tmp;
}	t_redir;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
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

int tokenize(t_process **process, t_env **env, char *line);
void    parse_redir(t_process *process);
void    parse_cmd(t_process *process);
char    *ft_strndup(const char *s, int n);
int     ft_strcmp(const char *s1, const char *s2);
void    create_env_list(t_env **env, char **envp);
void    replace_process_resources(t_process *process, t_env **env);
char    *search_env_value(t_env **env, char *search);
int    check_syntax(t_process *process);
void    check_redir_files(t_process *process);
void    free_redir_list(t_redir *redir);
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
void	add_env(t_env **env, char *key, char *value);
void	delete_env(t_env **env, char *del_key);
char	*search_env_value(t_env **env, char *search);
void	set_terminal_print_off(void);

void all_signal();

void	main_sigint_handler(int sign);
#endif