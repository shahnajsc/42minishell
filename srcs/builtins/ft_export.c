#include "minishell.h"

t_env 	*find_env_var(t_env *env, char *key)
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
int 	is_invalid_identifier(char *identifier, char *arg)
{
	int 	i;

	if (!identifier || (!ft_isalpha(identifier[0]) && identifier[0] != '_'))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("`: not a valid identifier", STDERR_FILENO);
		return (1);
	}
	i = 0;
	while(identifier[++i] != '\0')
	{
		if (ft_isalnum(identifier[i]) || identifier[i] == '_')
			return (0);
	}
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("`: not a valid identifier", STDERR_FILENO);
	return (1);
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
char  	*set_key(char *arg, char **sign)
{
	char 		*key;
	int 		key_len;

	key_len = *sign - arg;
	key = ft_strndup(arg, key_len);
	if (!key)
		return (NULL);
	return (key); 
}
int		set_env_variable(t_mshell *mshell, char **args, int i, int error_code)
{
	char 		*sign;
	char 		*identifier;

	while (args[++i] != NULL)
	{
		sign = ft_strchr(args[i], '=');
		if (!sign)
		{
			if (is_invalid_identifier(args[i], args[i]))
				error_code = 1;
			else
				process_without_sign(&mshell->env, args[i]);
		}
		else
		{
			identifier = set_key(args[i], &sign);
			if (is_invalid_identifier(identifier, args[i]))
				error_code = 1;
			else
				process_with_sign(&mshell->env, args[i], sign);				
		}
	}
	mshell->exit_code = error_code;
	return (error_code);
}
void 	print_export(t_env *env)
{
	int 	i;

	i = 0;
	while (env[i].key != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env[i].key, 1);
		if (env[i].value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env[i].value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
}

int 	ft_export(t_mshell *mshell, char **args)
{
	// check if the string is empty
	if (!args[1])
		print_export(mshell->env);
	if (set_env_variable(mshell, args, 0, 0))
		return (1);
	return (0);
}
