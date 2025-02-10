#include "minishell.h"

t_env 	*find_env_var(t_env *env, char *key)
{
	int		i;

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
		new_env[j].key = (*env)[j].key;
		new_env[j].value = (*env)[j].value;
		j++;
	}
	new_env[i].key = ft_strdup(key);
    new_env[i].value = value ? ft_strdup(value) : NULL;
    new_env[i + 1].key = NULL;
    new_env[i + 1].value = NULL;
	free(*env);
	*env = new_env;
	//   j = 0;
    // while ((*env)[j].key != NULL)
    // {
    //     printf("%s=%s\n", (*env)[j].key, (*env)[j].value);
    //     j++;
    // }
}
void 	export_var(t_env **env, char *str)
{
	t_env 	*variable;
	char 	*value;
	char 	*key;
	char 	*sign;

	sign = ft_strchr(str, '=');
	if (!sign)
	{
		if (!find_env_var(*env, str))
			add_env_var(env, str, NULL);
		return ;
	}
	key = ft_strndup(str, sign - str);
	value = ft_strdup(sign + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return ;
	}
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
void 	ft_export(t_env *env)
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

