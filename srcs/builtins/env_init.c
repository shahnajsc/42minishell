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
		(*env).value = ft_strdup(*sign + 1);
		if (!(*env).key || !(*env).value) 
			return (NULL);
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

int	duplicate_env(t_env **env, char **envp)
{
	char	*sign;
	int		i;

	i = -1;
	while (++i < envp_size(envp))
	{
		sign = ft_strchr(envp[i], '=');
		if (!set_key_value(&((*env)[i]), envp[i], &sign))
		{    
			free_env(*env);
			return(-1);
		}
	}
	(*env)[i].key = NULL;
	(*env)[i].value = NULL;
	return (0);
}

int 	mshell_level(t_env **env)
{
	t_env 		*shlvl;
	char 		*new_lvl;
	int 		nbr;

	shlvl = get_env_var(*env, "SHLVL");
	if (!shlvl || !shlvl->value)
		add_env_var(env, "SHLVL", "1");
	else 
	{
		nbr = ft_atoi(shlvl->value);
		new_lvl = ft_itoa(nbr + 1);
		if (nbr < 999)
		{
			free(shlvl->value);
			shlvl->value = new_lvl;
		}
		else
			mshell_lvl_error(env, new_lvl);
		//program should terminate
	}
	return (0);
}
t_env	*init_env(char **envp)
{
	t_env 		*env_list;
	int 		size;

	size = envp_size(envp);
	env_list = malloc(sizeof(t_env) * (size + 1));
	if (!env_list)
	{
		ft_putendl_fd("minishell: Allocation faild for env", STDERR_FILENO);
		return(NULL);
	}
	ft_memset(env_list, 0, sizeof(t_env) * (size + 1));
	if (duplicate_env(&env_list, envp) != 0)
	{
		free(env_list);
		return (NULL);
	}
	if (mshell_level(&env_list))
	{
		free(env_list);
		return(NULL);
	}
	return (env_list);
}
