#include "../include/parse.h"

char	*get_path_value(char *envp)
{
	int		i;
	char	*value;
	int		value_len;

	value_len = 0;
	while (envp[value_len])
		value_len++;
	value = (char *)malloc(sizeof(char) * (value_len + 1));
	i = 0;
	while (i < value_len)
	{
		value[i] = envp[i];
		i++;
	}
	value[i] = '\0';
	return (value);
}

char	*get_path_key(char *envp)
{
	int		i;
	char	*key;
	int		key_len;

	key_len = 0;
	while (envp[key_len] && (envp[key_len] != '='))
		key_len++;
	key = (char *)malloc(sizeof(char) * (key_len + 1));
	i = 0;
	while (i < key_len)
	{
		key[i] = envp[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}
