
#include "../include/parse.h"

char	*get_path_value(char *envp);
char	*get_path_key(char *envp);

void	add_env(t_env **env, char *key, char *value)
{
	t_env	*new_env;
	t_env	*last_env;

	new_env = (t_env *)malloc(sizeof(t_env));
	new_env->key = key;
	new_env->value = value;
	new_env->next = NULL;
	if (*env != NULL)
	{
		last_env = *env;
		while (last_env->next)
			last_env = last_env->next;
		last_env->next = new_env;
	}
	else
		*env = new_env;
}

void	delete_env(t_env **env, char *del_key)
{
	t_env	*prev;
	t_env	*delete_env;

	prev = *env;
	if (!ft_strcmp(prev->key, del_key))
	{
		delete_env = prev;
		*env = delete_env->next;
		return (free(delete_env));
	}
	while (prev)
	{
		if (prev->next && !ft_strcmp(prev->next->key, del_key))
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

char	*get_env_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	if (str[0] && (ft_isdigit(str[0]) || (str[0] == '?')))
		i = 1;
	else
	{
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
	}
	key = ft_strndup(str, i);
	return (key);
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
	char	*key;
	char	*value;

	while (*envp)
	{
		key = get_path_key(*envp);
		value = get_path_value(&(*envp)[ft_strlen(key) + 1]);
		if (value == NULL)
			add_env(env, ft_strdup(key), ft_strdup(""));
		else
			add_env(env, ft_strdup(key), ft_strdup(value));
		i = -1;
		free(key);
		free(value);
		envp++;
	}
}
