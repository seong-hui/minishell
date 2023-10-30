/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:11:51 by moonseonghu       #+#    #+#             */
/*   Updated: 2023/10/30 21:50:23 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void execute_heredoc(t_process *process, t_redir *redir)
{
    char *buffer;

    while (1)
    {
        buffer = readline("> ");
        if (buffer == NULL)
            break;
        if (!ft_strcmp(buffer, redir->file))
        {
            free(buffer);
            break;
        }
        ft_putstr_fd(buffer, process->infile_fd);
        ft_putstr_fd("\n", process->infile_fd);
        free(buffer);
    }
}

char *make_tmp_heredoc()
{
    char *tmp_heredoc;
    int i;

    i = 0;
    while (1)
    {
        tmp_heredoc = ft_strdup(ft_strjoin("tmp_file", ft_itoa(i)));
        if (open(tmp_heredoc, O_RDONLY) == -1)
        {
            printf("%s\n", tmp_heredoc);
            return (tmp_heredoc);
        }
        i++;
    }
    return (NULL);
}

void check_heredoc(t_process *process)
{
    // char *tmp_heredoc;
    t_redir *tmp_redir;
    int i;

    i = 0;
    while (process)
    {
        tmp_redir = process->redir;
        while (tmp_redir)
        {
            if (tmp_redir->type == T_REDIR_HEREDOC)
            {
                tmp_redir->tmp = make_tmp_heredoc();
                process->infile_fd = open(tmp_redir->tmp, O_RDWR | O_CREAT | O_TRUNC, 0644);
                execute_heredoc(process, tmp_redir);
                close(process->infile_fd);
            }
            tmp_redir = tmp_redir->next;
        }
        process = process->next;
    }
}
