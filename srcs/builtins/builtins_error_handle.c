#include "minishell.h"

int 	builtins_error(char *args, t_error err, char *msg, char *free_str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	if (args[1])
		ft_putstr_fd(args, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (err == NO_FILE)
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
	if (err == NOT_DIR)
		ft_putendl_fd("Not a directory", STDERR_FILENO);
	if (err == NO_PERM)
		ft_putendl_fd("Permission denied", STDERR_FILENO);
	if (err == UNSET_HOME)
		ft_putendl_fd("HOME not set", STDERR_FILENO);
	else
		ft_putendl_fd(msg, STDERR_FILENO);
	if (free_str)
		free(free_str);
	return (1);
}
void 	 free_env(t_env *env, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(env[i].key);
		free(env[i].value);
		i++;
	}
	free(env);
	env = NULL;
}

