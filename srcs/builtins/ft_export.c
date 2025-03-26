#include "minishell.h"

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

static void	print_export(t_env *env)
{
	int	i;

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

int	ft_export(t_mshell *mshell, char **args)
{
	int status;

	if (!mshell || !mshell->env || !args)
		return (0);
	status = 0;
	if (!args[1])
		print_export(mshell->env);
	else
		set_env_var(mshell, args, &status);
	return (status);
}
