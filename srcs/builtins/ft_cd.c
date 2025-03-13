#include <minishell.h>

static char 	*home_directory(t_env **env, char **dir)
{
	t_env 	*variable;

	variable = get_env_var(*env, "HOME");
	if (!variable || !variable->value)
		return (NULL);
	*dir = ft_strdup(variable->value);
	if (!*dir)
		return (NULL);
	return (*dir);
}
static char 	*get_target_directory(t_env **env, char *directory_arg)
{
	char *target;

	if (!directory_arg || ft_strcmp(directory_arg, "~") == 0)
		return (home_directory(env, &target));
	else
		target = ft_strdup(directory_arg);
	return (target);
}
static int 	is_invalid_directory(char **args, char *file)
{
	struct stat	sb;

	if (args[1] && args[2])
		return (MANY_ARGS);
	if (stat(file, &sb) == -1)
		return (NO_FILE);
	if (!S_ISDIR(sb.st_mode))
		return (NOT_DIR);
	if ((sb.st_mode & (S_IRUSR | S_IRGRP)) == 0
		|| (sb.st_mode & (S_IWUSR | S_IWGRP)) == 0
		|| (sb.st_mode & (S_IXUSR | S_IXGRP)) == 0)
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
		return (free(target), FAILURE);
	free(target);
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

	if (!*args[1])
		return (0);
	status_code = handle_cd(mshell, args);
	mshell->exit_code = status_code;
	return (status_code);
}
