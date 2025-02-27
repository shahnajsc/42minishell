#include <minishell.h>

t_built_state 	*init_built_state()
{
	t_built_state *state;

	state = (t_built_state *)malloc(sizeof(t_built_state));
	if (!state)
	{
		ft_putendl_fd("minishell: shell state", STDERR_FILENO);
		return (NULL);
	}
	state->pwd = getcwd(NULL, 0);
	if (!state->pwd)
	{
		free(state->pwd);
		ft_putendl_fd("minishell: getcwd failed", STDERR_FILENO);
		return (NULL);
	}
	state->old_pwd = NULL;
	state->pwd_exec = 0;
	state->oldpwd_exec = 0;
	return (state);
}

int shell_state(t_mshell *mshell, char *oldpwd, char *pwd)
{
	char *new_oldpwd;
	char *new_pwd;

	new_oldpwd = ft_strdup(oldpwd);
	new_pwd = ft_strdup(pwd);
	if (!new_oldpwd || !new_pwd)
	{
		free(new_oldpwd);
		free(new_pwd);
		mshell->b_state->pwd = getcwd(NULL, 0);
		mshell->b_state->old_pwd = NULL;
		if (!mshell->b_state->pwd)
			return(builtins_error(NULL, CMN_ERR, "minishell: getcwd failed for state->pwd", NULL));
		//ft_putendl_fd("minishell: shell state allocation failed", STDERR_FILENO);
	}
	free(mshell->b_state->old_pwd);
	free(mshell->b_state->pwd);
	mshell->b_state->old_pwd = new_oldpwd;
	mshell->b_state->pwd = new_pwd;
	mshell->b_state->pwd_exec = (find_env_var(mshell->env, "PWD") == NULL);
	mshell->b_state->oldpwd_exec = (find_env_var(mshell->env, "OLDPWD") == NULL);
	return (SUCSSES);
}

void	update_cd_env(t_env **env, const char *key, const char *set_path)
{
	t_env	*variable;
	char	*temp;

	variable = find_env_var(*env, (char *)key);
	if (!variable)
		return ;
	temp = ft_strdup(set_path);
	if (!temp)
	{
		ft_putendl_fd("Error: allocation failed", STDERR_FILENO);
		return ;
	}
	free(variable->value);
	variable->value = temp;
}
int 	home_directory(t_env **env, char **path)
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
int 	validate_directory(t_env **env, char **args)
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

void	update_built_state(t_mshell *mshell, char *oldpwd, char *pwd)
{
	shell_state(mshell, oldpwd, pwd);
	if (find_env_var(mshell->env, "OLDPWD"))
		update_cd_env(&mshell->env, "OLDPWD", oldpwd);
	if (find_env_var(mshell->env, "PWD"))
		update_cd_env(&mshell->env, "PWD", pwd);
}

int ft_cd(t_mshell *mshell, char **args)
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
