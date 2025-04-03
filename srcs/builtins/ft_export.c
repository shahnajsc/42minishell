#include "minishell.h"

void	swap_env(t_env *a, t_env *b)
{
	t_env	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_env(t_env *env)
{
	int	swapped;
	int	i;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (env[i].key != NULL && env[i + 1].key != NULL)
		{
			if (compare_keys(env[i].key, env[i + 1].key) > 0)
			{
				swap_env(&env[i], &env[i + 1]);
				swapped = 1;
			}
			i++;
		}
	}
}

static void	set_env_var(t_mshell *mshell, char **args, int *status_code)
{
	char	*sign;
	int		i;

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

static int	export_copy(t_env *dest, t_env *src)
{
	if (!src || !dest)
		return (EXIT_FAILURE);
	if (src->key)
	{
		dest->key = ft_strdup(src->key);
		if (!dest->key)
			return (EXIT_FAILURE);
	}
	else
		dest->key = NULL;
	if (src->value)
	{
		dest->value = ft_strdup(src->value);
		if (!dest->value)
		{
			free(dest->key);
			return (EXIT_FAILURE);
		}
	}
	else
		dest->value = NULL;
	return (EXIT_SUCCESS);
}

static int	export_duplicate(t_env **copy_env, t_env *env)
{
	int	count;
	int	i;

	count = 0;
	while (env[count].key != NULL)
		count++;
	*copy_env = malloc(sizeof(t_env) * (count + 1));
	if (!*copy_env)
		return (EXIT_FAILURE);
	i = 0;
	while (i < count)
	{
		if (export_copy(&(*copy_env)[i], &env[i]))
		{
			free_env(*copy_env);
			return (EXIT_FAILURE);
		}
		i++;
	}
	(*copy_env)[count].key = NULL;
	(*copy_env)[count].value = NULL;
	return (EXIT_SUCCESS);
}

static void	print_export(t_env *env)
{
	t_env	*copy_env;
	int		i;

	if (export_duplicate(&copy_env, env) != EXIT_SUCCESS)
		return ;
	sort_env(copy_env);
	i = 0;
	while (copy_env[i].key != NULL)
	{
        if (ft_strcmp(copy_env[i].key, "_") != 0)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(copy_env[i].key, STDOUT_FILENO);
			if (copy_env[i].value)
			{
				ft_putstr_fd("=\"", STDOUT_FILENO);
				ft_putstr_fd(copy_env[i].value, STDOUT_FILENO);
				ft_putstr_fd("\"", STDOUT_FILENO);
			}
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;	
	}
	free_env(copy_env);
}

int	ft_export(t_mshell *mshell, char **args)
{
	int	status;

	if (!mshell || !mshell->env || !args)
		return (0);
	status = 0;
	if (!args[1])
		print_export(mshell->env);
	else
		set_env_var(mshell, args, &status);
	return (status);
}
