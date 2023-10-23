/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooypark <jooypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:29:40 by jooypark          #+#    #+#             */
/*   Updated: 2023/10/22 22:13:45 by jooypark         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

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
}	t_redir;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_process
{
	t_redir				*redir;
	char				*cmd_line;
	char				**cmd;
	struct s_process	*next;
}	t_process;

int	tokenize(t_process **process, t_env **env, char *line);
void	parse_redir(t_process *process);
void	parse_cmd(t_process *process);
char	*ft_strndup(const char *s, int n);
int		ft_strcmp(const char *s1, const char *s2);
void	create_env_list(t_env **env, char **envp);
void	replace_process_resources(t_process *process, t_env **env);
char	*search_env_value(t_env **env, char *search);
void	check_syntax(t_process *process);

void	free_redir_list(t_redir *redir);
void	free_process_list(t_process **process);
void	free_env(t_env *env);
void	free_env_list(t_env *env);

int	in_charset(char c, char *charset);
void	print_syntax_error(char *str);
void	detect_signal(void);
void	signal_handler(int signo);

void	set_terminal_print_off(void);
void	set_terminal_print_on(void);

#endif