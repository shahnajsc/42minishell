#include <minishell.h>

static int 	home_directory(t_env **env, char **path)
{
	t_env 	*variable;

	variable = find_env_var(*env, "HOME");
	if (!variable || !variable->value)
		return (1); 
	if (*path && *path != variable->value)
		free(*path);
	*path = ft_strdup(variable->value);
	if (!*path)
		return (1);
	return (SUCSSES);
}
static int 	validate_directory(t_env **env, char **args)
{
	struct stat	file_stat;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		if (home_directory(env, &args[1]))
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

int handle_cd(t_mshell *mshell, char **args)
{
	char 			*oldpwd;
	char 			*pwd;
	t_error 		check;

	if (args[1] && args[2])
		return (builtins_error(args, TOO_MANY_ARGS, NULL, NULL));
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (builtins_error(args, CMN_ERR, "getcwd failed for oldpwd", NULL));
	check = validate_directory(&mshell->env, args);
	if (check != SUCSSES)
		return (builtins_error(args, check, NULL, oldpwd));
	if (chdir(args[1]) == -1)
		return (builtins_error(NULL, CMN_ERR, "chdir failed", oldpwd));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (builtins_error(args, CMN_ERR, "getcwd failed for pwd", NULL));
	update_built_state(mshell, oldpwd, pwd);
	free(oldpwd);
	free(pwd);
	return (SUCSSES);
}
int 	ft_cd(t_mshell *mshell, char **args)
{
	int 	error_code;

	error_code = 0;
	if (handle_cd(mshell, args))
		error_code = 1;
	mshell->exit_code = error_code;
	printf("%d\n", error_code);
	return (error_code);
}
