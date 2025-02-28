#include "minishell.h"

int 	builtins_error(char **args, t_error err, char *msg, char *free_str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(args[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (args[1] && !args[2])  // check this
		ft_putstr_fd(args[1], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (err == NO_FILE)
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
	if (err == NOT_DIR)
		ft_putendl_fd("Not a directory", STDERR_FILENO);
	if (err == NO_PERM)
		ft_putendl_fd("Permission denied", STDERR_FILENO);
	if (err == HOME_UNSET)
		ft_putendl_fd("HOME not set", STDERR_FILENO);
	if (err == TOO_MANY_ARGS)
		ft_putendl_fd("too many arguments", STDERR_FILENO);
	else
		ft_putendl_fd(msg, STDERR_FILENO);
	if (free_str)
		free(free_str);
	return (1);
}
int 	is_invalid_identifier(char *identifier, char *arg)
{
	int 	i;

	if (!identifier || (!ft_isalpha(identifier[0]) && identifier[0] != '_'))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("`: not a valid identifier", STDERR_FILENO);
		return (1);
	}
	i = 0;
	while(identifier[++i] != '\0')
	{
		if (ft_isalnum(identifier[i]) || identifier[i] == '_')
			return (0);
	}
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("`: not a valid identifier", STDERR_FILENO);
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

