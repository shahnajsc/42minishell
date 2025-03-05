#include "minishell.h"

char *ft_strndup(char *src, size_t n)
{
    size_t i;
    char *dest;

	if (!src)
		return (NULL);
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
t_env 	*get_env_var(t_env *env, char *key)
{
	int		i;

	if (!env || !key || !*key)
		return (NULL);
	i = 0;
	while (env[i].key != NULL)
	{
		if (ft_strcmp(env[i].key, key) == 0)
			return (&env[i]);
		i++;
	}
	return (NULL);
}
t_env  *allocate_new_env(t_env *old_env)
{
	t_env 	*new_env;
	int 	i;

	if (!old_env)
        return NULL;
	i = env_size(old_env);
	new_env = ft_calloc(sizeof(t_env), (i + 2));
	if (!new_env)
		return (NULL);
	return (new_env);
}
int 	env_size(t_env *env)
{
	int i;

	i = 0;
	while (env[i].key != NULL)
		i++;
	return (i);
}

int 	is_invalid_digit(char *arg)
{
	int 	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+') 
        i++;
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i++;
	}
	return (0);
}
