#include "minishell.h"

static void 	print_export(t_env *env)
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
	int 	status_code;

	status_code = 0;
	// check if the string is empty
	if (!args[1])
		print_export(mshell->env);
	else
		set_env_variable(mshell, args, &status_code);
	return (status_code);
}
