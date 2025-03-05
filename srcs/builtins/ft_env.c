#include "minishell.h"

// int env_size(char **env)
// {
// 	int i;

// 	i = 0;
// 	while (env[i])
// 		i++;
// 	return (i);
// }


char *ft_strndup(char *src, size_t n)
{
    size_t i;
    char *dest;

	i = 0;
	dest = malloc(sizeof(size_t) * (n + 1));
    if (!dest)
        return (NULL);
    while (i < n && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}
// void 	 free_env(t_env *env, int size)
// {
// 	int i;

// 	i = 0;
// 	while (i < size)
// 	{
// 		free(env[i].key);
// 		free(env[i].value);
// 		i++;
// 	}
// 	free(env);
// 	env = NULL;
// }

// t_env	*init_env(char **envp)
// {
// 	t_env 		*env_list;
// 	int 		size;

// 	size = env_size(envp);
// 	env_list = malloc(sizeof(t_env) * (size + 1));
// 	if (!env_list)
// 		return (NULL);
// 	ft_memset(env_list, 0, sizeof(t_env) * (size + 1));
// 	return (env_list);
// }

// t_env	*duplicate_env(char **envp, t_env **env)
// {
// 	char	*sign;
// 	int		i;

// 	*env = init_env(envp);
// 	if (!*env)
// 		return (NULL);

// 	i = 0;
// 	while (i < env_size(envp))
// 	{
// 		sign = ft_strchr(envp[i], '=');
// 		if (!sign)
// 		{
// 			(*env)[i].key = ft_strdup(envp[i]);  // Store key
//     		(*env)[i].value = NULL;
// 		}
// 		(*env)[i].key = ft_strndup(envp[i], sign - envp[i]);
// 		(*env)[i].value = ft_strdup(sign + 1);
// 		if (!(*env)[i].key || !(*env)[i].value)
// 		{
// 			free_env(*env, env_size(envp));
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	(*env)[i].key = NULL;
// 	(*env)[i].value = NULL;
// 	return (*env);
// }


// void	ft_env(t_env *env)
// {
// 	int i;

// 	i = 0;

// 	if (!env)
// 	{
// 		printf("Error: initialize environment\n");
// 		return ;
// 	}
// 	while (env[i].key != NULL)
// 	{
// 		if (env[i].value != NULL)
// 		{
// 			if (env[i].key && (env)[i].key[0] != '\0')
// 			{
// 				ft_putstr_fd(env[i].key, 1);
// 				ft_putchar_fd('=', 1);
// 			}
// 			ft_putstr_fd(env[i].value, 1);
// 			ft_putstr_fd("\n", 1);
// 		}
// 		i++;
// 	}
// 	// free_env(env, size);
// }

