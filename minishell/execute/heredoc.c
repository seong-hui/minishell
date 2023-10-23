/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:11:51 by moonseonghu       #+#    #+#             */
/*   Updated: 2023/10/19 18:27:49 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void execute_heredoc(t_process *process)
{
    
}

void check_heredoc(t_process *process)
{
    while(process->redir)
    {
        if (process->redir->type == T_REDIR_HEREDOC)
        {
            execute_heredoc(process);
            
        }
        process->redir = process->redir->next;
    }
}