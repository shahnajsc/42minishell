#include "minishell.h"

static int envp_size(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

static char *set_key_value(t_env *env, char *envp, char **sign)
{
	int 		key_len;

	if (*sign)
	{
		key_len = *sign - envp;
		(*env).key = ft_strndup(envp, key_len);
		if (!(*env).key)
			return (NULL);
		(*env).value = ft_strdup(*sign + 1);
		if (!(*env).value)
		{
			free((*env).key);
			return (NULL);
		}
	}
	else
	{
		(*env).key = ft_strdup(envp);
    	(*env).value = NULL;
		if (!(*env).key)
			return (NULL);
	}
	return (envp);
}

int	env_duplicate(t_env **env, char **envp)
{
	char	*sign;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		sign = ft_strchr(envp[i], '=');
		if (!set_key_value(&((*env)[i]), envp[i], &sign))
		{
			free_env(*env);
			return(-1);
		}
		i++;
	}
	(*env)[i].key = NULL;
	(*env)[i].value = NULL;
	return (0);
}

void 	mshell_level(t_env **env)
{
	t_env 		*shlvl;
	char 		*new_lvl;
	int 		nbr;

	shlvl = get_env_var(*env, "SHLVL");
	if (!shlvl || !shlvl->value)
	{
		add_env_var(env, "SHLVL", "1");
		return ;
	}
	nbr = ft_atoi(shlvl->value);
	new_lvl = ft_itoa(nbr + 1);
	if (nbr < 999)
	{
		free(shlvl->value);
		shlvl->value = ft_strdup(new_lvl);
		if (!shlvl->value )
		{
			free(new_lvl);
			return ;
		}
		free(new_lvl);
	}
	else
		mshell_lvl_error(env, new_lvl);   //program should terminate
}

t_env	*init_env(char **envp)
{
	t_env 		*env_list;
	int 		size;

	size = envp_size(envp);
	env_list = ft_calloc(sizeof(t_env), (size + 1));
	if (!env_list)
	{
		ft_putendl_fd("minishell: Allocation faild for env", STDERR_FILENO);
		return(NULL);
	}
	if (env_duplicate(&env_list, envp) != 0)
	{
		free(env_list);
		return (NULL);
	}
	mshell_level(&env_list);
	return (env_list);
}
