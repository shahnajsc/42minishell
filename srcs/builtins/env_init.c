#include "minishell.h"

static int	envp_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

static int	set_key_value(t_env *env, char *envp, char **sign)
{
	int	key_len;

	if (*sign)
	{
		key_len = *sign - envp;
		(*env).key = ft_strndup(envp, key_len);
		if (!(*env).key)
			return (FAILURE);
		(*env).value = ft_strdup(*sign + 1);
		if (!(*env).value)
			return (free((*env).key), 1);
	}
	else
	{
		(*env).key = ft_strdup(envp);
		(*env).value = NULL;
		if (!(*env).key)
			return (FAILURE);
	}
	return (0);
}

static int	env_duplicate(t_env **env, char **envp)
{
	char	*sign;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		sign = ft_strchr(envp[i], '=');
		if (set_key_value(&((*env)[i]), envp[i], &sign))
			return (free_env(*env), FAILURE);
		i++;
	}
	(*env)[i].key = NULL;
	(*env)[i].value = NULL;
	return (SUCSSES);
}

static void	mshell_level(t_env **env)
{
	t_env	*shlvl;
	char	*new_lvl;
	int		nbr;

	new_lvl = ft_strdup("1");
	shlvl = get_env_var(*env, "SHLVL");
	if (!shlvl || !shlvl->value)
		return (add_env_var(env, "SHLVL", new_lvl));
	free(new_lvl);
	nbr = ft_atoi(shlvl->value);
	new_lvl = ft_itoa(nbr + 1);
	if (nbr < 999)
	{
		free(shlvl->value);
		shlvl->value = ft_strdup(new_lvl);
		if (!shlvl->value)
			return (free(new_lvl));
		free(new_lvl);
	}
	else
		mshell_lvl_error(env, new_lvl, shlvl);
}

t_env	*init_env(char **envp)
{
	t_env	*env_list;

	if (!envp)
		return (0);
	env_list = ft_calloc(sizeof(t_env), (envp_size(envp) + 1));
	if (!env_list)
	{
		ft_putendl_fd("minishell: Allocation faild for env", STDERR_FILENO);
		return (NULL);
	}
	if (env_duplicate(&env_list, envp))
		return (free(env_list), NULL);
	mshell_level(&env_list);
	return (env_list);
}
