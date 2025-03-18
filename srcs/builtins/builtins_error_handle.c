#include "minishell.h"

int	cd_error(char **args, t_cd_error err)
{
	if (err != GETCWD)
		ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	if (args && err != MANY_ARGS && err != GETCWD)
		ft_putstr_fd(args[1], STDERR_FILENO);
	if (err == NO_FILE)
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	else if (err == NOT_DIR)
		ft_putendl_fd(": Not a directory", STDERR_FILENO);
	else if (err == NO_PERM)
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	else if (err == HOME_UNSET)
		ft_putendl_fd(": HOME not set", STDERR_FILENO);
	else if (err == MANY_ARGS)
		ft_putendl_fd("too many arguments", STDERR_FILENO);
	else if (err == GETCWD)
	{
		ft_putstr_fd("error retrieving current directory: ", STDERR_FILENO);
		ft_putstr_fd("getcwd: ", STDERR_FILENO);
		ft_putstr_fd("cannot access parent directories: ", STDERR_FILENO);
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
		return (0);
	}
	return (1);
}
int	builtins_error(char *arg, char *err_msg, char *free_str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (arg)
		ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(err_msg, STDERR_FILENO);
	if (free_str)
		free(free_str);
	return (1);
}

int	is_invalid_identifier(char *identifier)
{
	int	i;

	if (!identifier || (!ft_isalpha(identifier[0]) && identifier[0] != '_'))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(identifier, STDERR_FILENO);
		ft_putendl_fd("`: not a valid identifier", STDERR_FILENO);
		return (1);
	}
	i = 1;
	while (identifier[i] != '\0' && identifier[i] != '=')
	{
		if (!ft_isalnum(identifier[i]) && identifier[i] != '_')
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(identifier, STDERR_FILENO);
			ft_putendl_fd("`: not a valid identifier", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

int	mshell_lvl_error(t_env **env, char *new_lvl)
{
	ft_putstr_fd("minishell: warning: mshell level (", STDERR_FILENO);
	ft_putstr_fd(new_lvl, STDERR_FILENO);
	ft_putendl_fd(") too high, resetting to 1", STDERR_FILENO);
	free(new_lvl);
	free_env(*env);
	exit(EXIT_FAILURE);
}
void	free_env(t_env *env)
{
	int	i;

	i = 0;
	while (env[i].key != NULL)
	{
		free(env[i].key);
		free(env[i].value);
		i++;
	}
	free(env);
}
