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

int handle_cd(t_mshell *mshell, char **args, char **oldpwd, char **pwd)
{
	t_cd_error 		status_code;

	status_code = 0;
	if (args[2])
		return (cd_error(args, TOO_MANY_ARGS));
	*oldpwd = getcwd(NULL, 0);
	if (!*oldpwd)
		return (builtins_error(args[0], "getcwd failed for oldpwd", NULL));
	status_code = is_invalid_directory(&mshell->env, args);
	if (status_code)
		return (cd_error(args, status_code));
	if (chdir(args[1]) == -1)
		return (builtins_error(args[0],"chdir failed", *oldpwd));
	*pwd = getcwd(NULL, 0);
	if (!*pwd)
		return (builtins_error(args[0],"getcwd failed for pwd", NULL));
	return (update_env_state(mshell, oldpwd, pwd));
}
int 	ft_cd(t_mshell *mshell, char **args)
{
	int			status_code;
	char 		*oldpwd;
	char 		*pwd;

	pwd = NULL;
	oldpwd = NULL;
	status_code = handle_cd(mshell, args, &oldpwd, &pwd);
	free(oldpwd);
	free(pwd);
	return (status_code);
}