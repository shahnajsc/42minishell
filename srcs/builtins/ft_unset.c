#include "minishell.h"

static t_env	*allocate_env_size(int env_size, int key_len)
{
	int		new_env_size;
	t_env	*new_env;

	new_env_size = env_size - key_len;
	new_env = ft_calloc(new_env_size + 1, sizeof(t_env));
	if (!new_env)
		return (NULL);
	return (new_env);
}

static int	should_unset_var(t_env *env_var, char **keys)
{
	int	i;

	i = 0;
	while (keys[i] != NULL)
	{
		if (strcmp(env_var->key, keys[i]) == 0)
			return (1); // unset if there's a match
		i++;
	}
	return (0); // No match found
}

static int	count_keys(t_env *env, char **keys)
{
	int	count;
	int	i;

	i = 1;
	count = 0;
	while (keys[i] != NULL)
	{
		if (get_env_var(env, keys[i]))
			count++;
		i++;
	}
	return (count);
}
static int	copy_variable(t_env *src_var, t_env *dest_var)
{
	dest_var->key = ft_strdup(src_var->key);
	if (!dest_var->key)
		return (0);
	if (src_var->value)
	{
		dest_var->value = ft_strdup(src_var->value);
		if (!dest_var->value)
			return (free(dest_var->key), 0);
	}
	else
		dest_var->value = NULL;
	return (1);
}

int	ft_unset(t_mshell *mshell, char **keys, int i, int index)
{
	int		env_count;
	t_env	*new_env;

	if (!mshell || !mshell->env || !keys || !*keys)
		return (0);
	env_count = env_size(mshell->env);
	new_env = allocate_env_size(env_count, count_keys(mshell->env, keys));
	if (!new_env)
		return (0);
	while (i < env_count)
	{
		if (!should_unset_var(&mshell->env[i], keys))
		{
			if (!copy_variable(&mshell->env[i], &new_env[index]))
				return (free_env(new_env), 0);
			index++;
		}
		i++;
	}
	new_env[index].key = NULL;
	new_env[index].value = NULL;
	free_env(mshell->env);
	mshell->env = new_env;
	mshell->exit_code = 0;
	return (0);
}
