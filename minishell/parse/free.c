#include "../include/parse.h"

void	free_redir_list(t_redir *redir)
{
	t_redir	*next;

	while (redir)
	{
		free(redir->file);
		next = redir->next;
		redir->next = NULL;
		free(redir);
		redir = next;
	}
}

void	free_process_list(t_process **process)
{
	t_process	*cur;
	t_process	*next;
	int			i;

	cur = *process;
	while (cur)
	{
		free_redir_list(cur->redir);
		free(cur->cmd_line);
		i = 0;
		while (cur->cmd && cur->cmd[i])
			free(cur->cmd[i++]);
		free(cur->cmd);
		next = cur->next;
		cur->next = NULL;
		free(cur);
		cur = next;
	}
}

void	free_env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void	free_env_list(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		env->next = NULL;
		free_env(env);
		env = next;
	}
}
