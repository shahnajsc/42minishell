#include "minishell.h"

static void 	print_env(t_env *env)
{
	int 	i;

	i = -1;
	while (env[++i].key != NULL)
	{
		if (env[i].value != NULL)
		{
			if (env[i].key && (env)[i].key[0] != '\0')
			{
				ft_putstr_fd(env[i].key, STDOUT_FILENO);
				ft_putchar_fd('=', STDOUT_FILENO);
			}
			ft_putendl_fd(env[i].value, STDOUT_FILENO);
		}
	}
}
int		ft_env(t_mshell *mshell, char **args)
{
	int 	status_code;

	status_code = 0;
	if (!args[1])
		print_env(mshell->env);
	else
	{
		ft_putstr_fd("env: `", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd("`: No such file or directory", STDERR_FILENO);
		status_code = 127;
	}
	mshell->exit_code = status_code;
	return (status_code);
}