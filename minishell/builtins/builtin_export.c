/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonseonghui <moonseonghui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:33:09 by seonghmo          #+#    #+#             */
/*   Updated: 2023/10/25 22:43:28 by moonseonghu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

t_env* sort_list(t_env *env)
{
	t_env *start;
	char *tmp;
	
	start = env;
	while(env->next)
	{
		if (ft_strcmp(env->key, env->next->key) > 0)
		{
			tmp = env->key;
			env->key = env->next->key;
			env->next->key = tmp;
			env = start;
		}
		else
			env = env->next;
	}
	env = start;
	return(env);
}

void check_value(char *env_str)
{
	int	i;

	i = 0;
	while(env_str[i])
	{
		if (env_str[i] == '=')
			return;
	}
}

void	replace_env(t_env **env, char *key, char *value)
{
	t_env	*tmp_env;

	tmp_env = *env;
    if (value)
    {
	    while (tmp_env)
        {
            if (ft_strcmp(tmp_env->key, key) == 0)
            {
                tmp_env->value = value;
                break;
            }
            tmp_env = tmp_env->next;      
        }
    }
}

int search_env_key(t_env **env, char *search)
{
	t_env	*target;

	target = *env;
	while (target)
	{
		if (ft_strcmp(target->key, search) == 0)
			return (1);
		target = target->next;
	}
	return (0);
}

void add_export(t_process *process, t_env *env)
{
	int i;

	i = 1;
	char *key;
	char *value;
	char **tmp;
    char *cmd;
	while(process->cmd[i])
	{
        cmd = process->cmd[i];
		key = get_path_key(cmd);
       if (ft_strlen(process->cmd[i]) > ft_strlen(key) + 1)
		    value = get_path_value(&process->cmd[i][ft_strlen(key) + 1]);
        else
            value = NULL;
		if ((process->cmd[i][0] == '_' && process->cmd[i][1]) 
			|| ft_isalpha(process->cmd[i][0]))
		{
            if (search_env_key(&env, key))
                replace_env(&env, key, value);
            else
			    add_env(&env, key, value);
		}
        else
        {
            write(2, "export: ", ft_strlen("export: "));
            write(2, process->cmd[i], ft_strlen(process->cmd[i]));
			write(2, " : not a valid identifier\n", ft_strlen(" : not a valid identifier\n"));
        }
        i++;
	}
}

t_env *copy_env(t_env *env)
{
    t_env *copy = NULL; 
    t_env *new_env;
    
    while (env)
    {
        new_env = (t_env *)malloc(sizeof(t_env));
        if (!new_env)
        {
            free_env_list(copy);
            return NULL;
        }
        if (env->key)
            new_env->key = ft_strdup(env->key);
        else
             new_env->key = NULL;
        if (env->value)
            new_env->value = ft_strdup(env->value);
        else   
            new_env->value = NULL;
        new_env->next = NULL;
        if (copy == NULL)
            copy = new_env;
        else
        {
            t_env *temp = copy;
            while (temp->next)
                temp = temp->next;
            temp->next = new_env;
        }
        env = env->next;
    }
    return copy;
}


void	builtin_export(t_process *process, t_env *env, int fd)
{
	t_env *env_s;
	env_s = env;
	if (!process->cmd[1])
	{
        env_s = copy_env(env_s);
        env_s = sort_list(env_s);
	 	while (env_s)
    	{
			ft_putstr_fd("declare -x ", fd);
         	ft_putstr_fd(env_s->key, fd);
            if (env_s->value)
            {
         	    ft_putstr_fd("=", fd);
			    ft_putstr_fd("\"", fd);
         	    ft_putstr_fd(env_s->value, fd);
		 	    ft_putstr_fd("\"", fd);
            }
            ft_putstr_fd("\n", fd);
        	env_s = env_s->next;
    	}
	}
	else
	{
		add_export(process, env);
	}
}
