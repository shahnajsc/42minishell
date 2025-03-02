#include "minishell.h"

int cd_error(char **args, t_cd_error err)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	// if (args[1] && !args[2])    // needed?
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
	return (1);
}
int 	builtins_error(char *err_msg, char *free_str)
{
	if (free_str)
		free(free_str);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}
int 	is_invalid_identifier(char *identifier)
{
	int 	i;

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
	exit (EXIT_FAILURE); 
}
void 	free_env(t_env *env)
{
	int i;

	i = 0;
	while (env[i].key != NULL)
	{
		free(env[i].key);
		free(env[i].value);
		i++;
	}
	free(env);
}

