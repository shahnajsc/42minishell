#include <minishell.h>

static char 	*home_directory(t_env **env, char **path)
{
	t_env 	*variable;

	variable = get_env_var(*env, "HOME");
	if (!variable || !variable->value)
		return (NULL);
	*path = ft_strdup(variable->value);
	if (!*path)
		return (NULL);
	return (*path);
}
static char 	*get_target_directory(t_env **env, char *directory_arg)
{
	char *home_dir;

	home_dir = home_directory(env, &home_dir);
	if (!directory_arg || ft_strcmp(directory_arg, "~") == 0)
		return (home_dir);
	free(home_dir);
	return (directory_arg);
}
static int 	is_invalid_directory(char **args, char *file)
{
	struct stat	file_stat;

	if (args[1] && args[2])
		return (MANY_ARGS);
	if (stat(file, &file_stat) == -1)
		return (NO_FILE);
	if (!S_ISDIR(file_stat.st_mode))
		return (NOT_DIR);
	if (access(file, R_OK | W_OK | X_OK) != 0)
		return (NO_PERM);
	return (SUCSSES);
}

static int handle_cd(t_mshell *mshell, char **args)
{
	t_cd_error 		error_code;
	char 			*new_pwd;
	char 			*target;

	target = get_target_directory(&mshell->env, args[1]);
	if (!target)
		return(cd_error(args, HOME_UNSET));
	error_code = is_invalid_directory(args, target);
	if (error_code != SUCSSES)
		return (cd_error(args, error_code));
	if (chdir(target) == -1)
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
