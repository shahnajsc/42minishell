#include "minishell.h"

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

static int copy_env(t_env *old_env, t_env *new_env)
{
    int 	i;

	i = 0;
    while (old_env[i].key != NULL) 
    {
        new_env[i].key = ft_strdup(old_env[i].key);
		if (old_env[i].value)
            new_env[i].value = ft_strdup(old_env[i].value);
		else
			new_env[i].value = NULL;
        if (!new_env[i].key || (!new_env[i].value && old_env[i].value))
		{
			free_env(new_env);
			return(free(new_env[i].key), 1);
		}
        i++;
    }
	return (0);
}
void   add_env_var(t_env **old_env, char *key, char *value)
{
	t_env 	*new_env;
	int 	i;
	
	new_env = allocate_new_env(*old_env);
	if (!new_env)
		return ;
	if (copy_env((*old_env), new_env))
		return (free(new_env));
	i = env_size(new_env);
	new_env[i].key = ft_strdup(key);
	if (value)
		new_env[i].value = ft_strdup(value);
	else
		new_env[i].value = NULL;
    new_env[i + 1].key = NULL;
    new_env[i + 1].value = NULL;
	free_env(*old_env);
	*old_env = new_env;
}

void 	process_without_sign(t_env **env, char *arg)
{
	if (!get_env_var(*env, arg))
		return (add_env_var(env, arg, NULL));
}

void 	process_with_sign(t_env **env, char *arg, char *sign)
{
	char 		*key;
	char 		*value;
	t_env 		*variable;

	key = ft_strndup(arg, sign - arg);
	value = ft_strdup(sign + 1);
	if (!key || !value)
		return (free(key));
	variable = get_env_var(*env, key);
	if (variable && variable->value)
	{
		free(variable->value);
		variable->value = value;
	}
	else
	{
		add_env_var(env, key, value);
		free(value);
	}
	free(key);
}
