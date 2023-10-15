/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghmo <seonghmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:35:59 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/16 05:23:35 by seonghmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

# define T_SIMPLE 0
# define T_PIPE 1
# define T_REDIR_INPUT 2
# define T_REDIR_OUTPUT 3
# define T_REDIR_HEREDOC 4
# define T_REDIR_APPEND 5

typedef struct s_redir
{
    int             type;
    char            *file;
    char            *tmp;
    struct s_redir  *next;
}   t_redir;
typedef struct s_process
{
    t_redir         *redir;
    char            **cmd;
    struct s_process  *next;
    int             pipefd[2];
    int             infile_fd;
    int             outfile_fd;
}   t_process;

typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
}   t_env;

int		ft_strncmp(const char *s1, const char *s2, int n);
char	**ft_split(char const *s, char c);
int		ft_strlen(char *s);
void	builtin_echo(t_process *process);
void builtin_pwd(t_process *process);
void builtin_cd(t_process *process);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	*ft_strrchr(char *s, int c);
void	check_biltins(t_process *process);
void process_start(t_process *process, char **envp);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);

#endif

