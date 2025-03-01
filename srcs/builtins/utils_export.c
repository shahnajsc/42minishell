#include "minishell.h"

void   add_env_var(t_env **env, char *key, char *value)
{
	int 	i;
	int 	j;
	t_env 	*new_env;

	i = 0;
	while ((*env)[i].key != NULL)
		i++;
	new_env = malloc(sizeof(t_env) * (i + 2));
	if (!new_env)
		return ;
	j = 0;
	while (j < i)
	{
		new_env[j].key = ft_strdup((*env)[j].key);
		new_env[j].value = (*env)[j].value ? ft_strdup((*env)[j].value) : NULL;
		if (!new_env[j].key || (!new_env[j].value && (*env)[j].value))
		{	
			free_env(new_env, j);
			printf("Error: allocation faild\n");
			return ;
		}
		j++;
	}
	new_env[i].key = ft_strdup(key);
    new_env[i].value = value ? ft_strdup(value) : NULL;
    new_env[i + 1].key = NULL;
    new_env[i + 1].value = NULL;
	free(*env);
	*env = new_env;
}


void 	process_without_sign(t_env **env, char *arg)
{
	if (!find_env_var(*env, arg))
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
	variable = find_env_var(*env, key);
	if (variable)
	{
		free(variable->value);
		variable->value = value;
	}
	else
		add_env_var(env, key, value);
	free(key);
}

char  	*get_key(char *key, char **sign)
{
	char 		*identifier;
	int 		identifier_len;

	identifier_len = *sign - key;
	identifier = ft_strndup(key, identifier_len);
	if (!identifier)
		return (NULL);
	return (identifier); 
}

void	set_env_variable(t_mshell *mshell, char **args, int *err_code)
{
	char 		*sign;
	char 		*identifier;
	int 		i; 

	i = -1;
	while (args[++i] != NULL)
	{
		sign = ft_strchr(args[i], '=');
		if (!sign)
		{
			if (is_invalid_identifier(args[i], args[i]))
				*err_code = 1;
			else
				process_without_sign(&mshell->env, args[i]);
		}
		else
		{
			identifier = get_key(args[i], &sign);
			if (is_invalid_identifier(identifier, args[i]))
				*err_code = 1;
			else
				process_with_sign(&mshell->env, args[i], sign);				
		}
	}
}
