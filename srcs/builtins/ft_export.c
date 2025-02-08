#include "minishell.h"


void 	ft_export(t_env *env, char **envp, char *str)
{
	char 	*sign;
	char 	*key;
	char 	*value;
	int 	size;
	int 	len;
	int 	i;
	// t_env 	*new_env;

	env = init_env(envp, env);


	sign = ft_strchr(str, '=');
	if (!sign)
		return ;
	len = sign - str;
	key = ft_strndup(str, len);
	value = ft_strdup(sign + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return ;
	}
	size = env_size(envp);
	i = 0;
	while (i < size)
	{
		if (ft_strcmp(env[i].key, key) == 0)
		{
			free(env[i].value);
			env[i].value = value;
			free(key);
			break ;
		}
		i++;
	}
	// new_env = malloc(sizeof(t_env) * (size + 2));
	// if (!new_env)
	// {
	// 	free(key);
	// 	free(value);
	// 	return ;
	// }
	// i = 0;
	// while (i < size)
	// {
	// 	new_env[i].key = env[i].key;
	// 	new_env[i].value = env[i].value;
	// 	i++;
	// }
	// new_env[i].key = key;
	// new_env[i].value = value;
	// new_env[i + 1].key = NULL;
	// new_env[i + 1].value = NULL;
	// free(env);
	// env = new_env;
// printf("%s=%s\n", new_env[0].key, new_env[0].value);
	int j = 0;
	
	while (j < size)
	{
		printf("%s=%s\n", env[j].key, env[j].value);
		j++;
	}


	// add_env_var(env, key, value);
	// free(key);
	free(value);
}

