#include "minishell.h"


///"srcs/includes/minishell.h"



int env_size(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	ft_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
}

char *ft_strndup(char *src, size_t n)
{
    size_t i = 0;
    char *dest = malloc(n + 1);  // Allocate memory (+1 for null terminator)

    if (!dest)
        return NULL;

    while (i < n && src[i] != '\0')  // Copy up to 'n' chars or until '\0'
    {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';  // Null-terminate the string
    return dest;
}


t_env	*init_struct(char **envp)
{
	t_env 		*env_list;
	int 		size;

	size = env_size(envp);
	env_list = malloc(sizeof(t_env) * (size + 1));
	if (!env_list)
		return (NULL);
	ft_memset(env_list, 0, sizeof(env_list) * size);
	return (env_list);
}

t_env	*init_env(char **envp)
{
	int i;
	char *sign;
	int key_len;
	t_env 	*env;
	int size;

	size = env_size(envp);
	env  = init_struct(envp);
	if (!env)
		return (NULL);
	i = 0;
	while (i <  size)
	{
		sign = ft_strchr(envp[i], '=');
		if (sign)
		{
			key_len = sign - envp[i];
			env[i].key = ft_strndup(envp[i], key_len);
			env[i].value = ft_strdup(sign + 1);
			if (!env[i].key || !env[i].value) 
			{
				free_env(env)
				return (NULL);
			}
		}
		i++;
	}
	env[size].key = '\0';
	env[size].value = '\0';
	return (env);
}

