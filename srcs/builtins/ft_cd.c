#include <minishell.h>

static int 	get_home_directory(t_env **env, char **path)
{
	t_env 	*variable;

	variable = get_env_var(*env, "HOME");
	if (!variable || !variable->value)
		return (1);
	if (*path && *path != variable->value)
		free(*path);
	*path = ft_strdup(variable->value);
	if (!*path)
		return (1);
	return (0);
}
static int 	is_invalid_directory(t_env **env, char **args)
{
	struct stat	file_stat;

	if (args[1] && args[2])
		return (MANY_ARGS);
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		if (get_home_directory(env, &args[1]))
			return (HOME_UNSET);
	}
	if (stat(args[1], &file_stat) == -1)
		return (NO_FILE);
	if (!S_ISDIR(file_stat.st_mode))
		return (NOT_DIR);
	if (access(args[1], R_OK | W_OK | X_OK) != 0)
		return (NO_PERM);
	return (SUCSSES);
}

static int handle_cd(t_mshell *mshell, char **args)
{
	t_cd_error 		error_code;
	char 			*new_pwd;

	error_code = is_invalid_directory(&mshell->env, args);
	if (error_code != SUCSSES)
		return (cd_error(args, error_code));
	if (chdir(args[1]) == -1)
		return (FAILURE);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (cd_error(args, GETCWD));
	if (update_env_state(mshell, new_pwd) != SUCSSES)
		return (FAILURE);
	return (SUCSSES);
}
int 	ft_cd(t_mshell *mshell, char **args)
{
	int			status_code;

	status_code = handle_cd(mshell, args);
	return (status_code);
}
