#include "parse.h"

void	print_syntax_error(char *str)
{
	ft_putendl_fd(str, 1);
	g_exit_code = 258;
}

void	check_syntax(t_process *process)
{
	t_redir	*cur_redir;

	if (process == NULL || process->cmd == NULL)
		print_syntax_error("minishell: syntax error: invalid syntax");
	cur_redir = process->redir;
	while (cur_redir)
	{
		if (cur_redir->file == NULL || *cur_redir->file == '\0')
			print_syntax_error("minishell: syntax error: invalid syntax");
		cur_redir = cur_redir->next;
	}
}

