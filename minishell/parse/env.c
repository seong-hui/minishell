#include "../include/parse.h"

void	free_env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void	add_env(t_env **env, char *key, char *value)
{
	t_env	*new_env;
	t_env	*last_env;

	new_env = (t_env *)malloc(sizeof(t_env));
	new_env->key = key;
	new_env->value = value;
	new_env->next = NULL;
	if (*env == NULL)
	{
		*env = new_env;
		return ;
	}
	else
	{
		last_env = *env;
		while (last_env->next)
			last_env = last_env->next;
		last_env->next = new_env;
	}
}

void	delete_env(t_env **env, char *del_key)
{
	t_env	*prev;
	t_env	*delete_env;

	prev = *env;
	while (prev)
	{
		if (prev->next
			&& !ft_strncmp(prev->next->key, del_key, ft_strlen(del_key)))
		{
			delete_env = prev->next;
			break ;
		}
		prev = prev->next;
	}
	if (prev == NULL)
		return ;
	prev->next = delete_env->next;
	delete_env->next = NULL;
	free_env(delete_env);
}

char	*search_env_value(t_env **env, char *search)
{
	t_env	*target;

	target = *env;
	while (target)
	{
		if (ft_strcmp(target->key, search) == 0)
			return (target->value);
		target = target->next;
	}
	return (NULL);
}

void	create_env_list(t_env **env, char **envp)
{
	int		i;
	char	**paths;

	while (*envp)
	{
		paths = ft_split(*envp, '=');
		add_env(env, ft_strdup(paths[0]), ft_strdup(paths[1]));
		i = -1;
		while (paths[++i])
			free(paths[i]);
		free(paths);
		envp++;
	}
}
