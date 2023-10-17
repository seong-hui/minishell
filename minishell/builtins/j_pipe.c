/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:37:50 by jonhan            #+#    #+#             */
/*   Updated: 2023/10/16 21:34:21 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_child(t_arg arg, char *argv[], char *envp[])
{
	arg.infile = open(argv[1], O_RDONLY);
	if (arg.infile == -1)
		exit(1);
	close(arg.fds_next[0]);
	dup2(arg.infile, STDIN_FILENO);
	dup2(arg.fds_next[1], STDOUT_FILENO);
	close(arg.fds_next[1]);
	close(arg.infile);
	arg.command = ft_split(argv[arg.index], ' ');
	arg.valid_cmd = valid(arg.path, arg.command[0]);
	if (execve(arg.valid_cmd, arg.command, envp) < 0)
	{
		ft_putstr_fd("bash: command not found\n", 2);
		exit(127);
	}
}

void	middle_child(t_arg arg, char *argv[], char *envp[])
{
	close(arg.fds_next[0]);
	close(arg.fds_prev[1]);
	dup2(arg.fds_prev[0], STDIN_FILENO);
	dup2(arg.fds_next[1], STDOUT_FILENO);
	close(arg.fds_prev[0]);
	close(arg.fds_next[1]);
	arg.command = ft_split(argv[arg.index], ' ');
	arg.valid_cmd = valid(arg.path, arg.command[0]);
	if (execve(arg.valid_cmd, arg.command, envp) < 0)
	{
		ft_putstr_fd("bash: command not found\n", 2);
		exit(127);
	}
}

void	last_child(t_arg arg, int argc, char *argv[], char *envp[])
{
	close(arg.fds_prev[1]);
	arg.outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (arg.outfile == -1)
		exit(1);
	dup2(arg.fds_prev[0], STDIN_FILENO);
	dup2(arg.outfile, STDOUT_FILENO);
	close(arg.fds_prev[0]);
	close(arg.outfile);
	arg.command = ft_split(argv[arg.index], ' ');
	arg.valid_cmd = valid(arg.path, arg.command[0]);
	if (execve(arg.valid_cmd, arg.command, envp) < 0)
	{
		ft_putstr_fd("bash: command not found\n", 2);
		exit(127);
	}
}

void	wait_child(pid_t pid, int argc)
{
	int	count;

	count = 0;
	while (pid != 0 && count < argc - 3)
	{
		if (waitpid(-1, 0, 0) < 0)
			return ;
		count++;
	}
	return ;
}

void	pipex(int argc, t_arg arg, char *argv[], char *envp[])
{
	pid_t	pid;

	arg.repeat_fork = -1;
    pipe(arg.fds_prev);
	while (++arg.repeat_fork < argc - 3)
	{
		if (exec->repeat_fork > 0)
	    {
		    close(exec->fds_prev[0]);
		    close(exec->fds_prev[1]);
	    }   
	    if (exec->repeat_fork != 0)
	    {
		    exec->fds_prev[0] = exec->fds_next[0];
		    exec->fds_prev[1] = exec->fds_next[1];
	    }
		arg.fds_prev[0] = arg.fds_next[0];
		arg.fds_prev[1] = arg.fds_next[1];
		if (arg.repeat_fork < argc - 4)
			pipe(arg.fds_next);
		pid = fork();
		if (pid == 0 && arg.repeat_fork == 0)
			first_child(arg, argv, envp);
		else if (pid == 0 && arg.repeat_fork == (argc - 4))
			last_child(arg, argc, argv, envp);
		else if (pid == 0)
			middle_child(arg, argv, envp);
		else
			arg.index++;
	}
	close_fd(&arg);
	wait_child(pid, argc);
}
