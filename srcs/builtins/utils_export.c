#include "minishell.h"

int copy_env(t_env *old_env, t_env *new_env)
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
			free(new_env[i].value);
			return(builtins_error("Allocation failed for new env", new_env[i].key));
		}
        i++;
    }
	return (0);
}

void   add_env_var(t_env **old_env, char *key, char *value)
{
	t_env 	*new_env;
	int 	i;
	if (!*old_env || !key || value)
		return ;	
	new_env = NULL;
	new_env = allocate_new_env(*old_env);
	if (!new_env)
		return ;
	if (copy_env((*old_env), new_env))
		return ;
	i = env_size(new_env);
	new_env[i].key = ft_strdup(key);
	if (value)
		new_env[i].value = ft_strdup(value);
	else
		new_env[i].value = NULL;
    new_env[i + 1].key = NULL;
    new_env[i + 1].value = NULL;
	free(*old_env);
	*old_env = new_env;
}

void 	process_without_sign(t_env **env, char *arg)
{
	if (!get_env_var(*env, arg))
		add_env_var(env, arg, NULL);
}

void 	process_with_sign(t_env **env, char *arg, char *sign)
{
	char 		*key;
	char 		*value;
	t_env 		*variable;

	key = ft_strndup(arg, sign - arg);
	value = ft_strdup(sign + 1);
	if (!key || !value)
		return ;
	variable = get_env_var(*env, key);
	if (variable)
	{
		free(variable->value);
		variable->value = value;
	}
	else
		add_env_var(env, key, value);
	free(key);
}

void	set_env_variable(t_mshell *mshell, char **args, int *status_code)
{
	char 		*sign;
	int 		i; 

	i = 1;
	while (args[i] != NULL)
	{
		if (is_invalid_identifier(args[i]))
			*status_code = 1;
		else
		{
			sign = ft_strchr(args[i], '=');
			if (!sign)
				process_without_sign(&mshell->env, args[i]);
			else
				process_with_sign(&mshell->env, args[i], sign);		
		}
		i++;	
	}
}
