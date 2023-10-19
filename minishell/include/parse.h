/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:29:40 by jooypark          #+#    #+#             */
/*   Updated: 2023/10/19 21:03:46 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define T_SIMPLE 0
# define T_PIPE 1
# define T_REDIR_INPUT 2
# define T_REDIR_OUTPUT 3
# define T_REDIR_HEREDOC 4
# define T_REDIR_APPEND 5

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
    t_redir         *redir;
    char            **cmd;
    struct s_process  *next;
    int             pipefd[2];
    int             infile_fd;
    int             outfile_fd;
    char				*cmd_line;
}   t_process;

void	tokenize(t_process **process, t_env **env, char *line, char **envp);
void	parse_redir(t_process *process);
void	parse_cmd(t_process *process);
char	*ft_strndup(const char *s, int n);
int		ft_strcmp(const char *s1, const char *s2);
void	create_env_list(t_env **env, char **envp);
void	replace_process_resources(t_process *process, t_env **env);
char	*search_env_value(t_env **env, char *search);
void    process_start(t_process *process, t_env *env);

#endif