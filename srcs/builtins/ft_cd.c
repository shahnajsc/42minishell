#include <minishell.h>

void 	update_env(t_env **env, const char *key, const char *set_path)
{
	int 	i;
	int 	j;
	char 	*temp;

	if (!env || !key || !*key || !set_path)
		return ;
	i = 0;
	while ((*env)[i].key != NULL)
		i++;
	j = 0;
	while (j < i)
	{
		if (ft_strcmp((*env)[j].key, (char *)key) == 0)
		{
			temp = ft_strdup(set_path);
			if (!temp)
			{
				printf("allocation failed\n");
				return ;
			}
			free((*env)[j].value);
			(*env)[j].value = temp;
			return ;
		}
		j++;
	}
}


int 	home_directory(t_env **env, const char **path)
{
	char 	*home;
	t_env 	*variable;

	home = NULL;
	if (!*path)
	{
		variable = find_env_var(*env, "HOME");
		if (!variable)
			return (1);
		home = variable->value;
		if (!home)
			return (1);  // minishell: cd: HOME not set
		*path = home;
	}
	return (0);
}
int 	validate_directory(t_env **env, const char *path)
{
	struct stat	path_stat;

	// if (path[1])  too many arguments
	if (home_directory(env, &path))
		return (UNSET_HOME);
	if (stat(path, &path_stat) == -1)
		return (NO_FILE);   // minishell: cd: hello: No such file or directory
	if (!S_ISDIR(path_stat.st_mode))
		return (NOT_DIR);  // minishell: cd: includes/minishell.h: Not a directory
	if (access(path, W_OK) != 0 || access(path, X_OK) != 0 || access(path, R_OK) != 0)
		return (NO_PERM);
	return (SUCSSES);
}
int change_directory(const char *path)
{
    if (chdir(path) == -1)
        return (1);
    return (0); 
}

t_shell_state 	*init_shell_state()
{
	t_shell_state *state;

	state = (t_shell_state *)malloc(sizeof(t_shell_state));
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

void update_shell_state(t_env **env, t_shell_state *state, char *oldpwd, char *pwd)
{
	char *new_oldpwd;
	char *new_pwd;

	new_oldpwd = ft_strdup(oldpwd);
	new_pwd = ft_strdup(pwd);
	if (!new_oldpwd || !new_pwd)
	{
		ft_putendl_fd("minishell: shell state allocation failed", STDERR_FILENO);
		free(new_oldpwd);
		free(new_pwd);
		state->pwd = getcwd(NULL, 0);
		state->old_pwd = NULL;
		if (!state->pwd)
			ft_putendl_fd("minishell: getcwd failed", STDERR_FILENO);
		return;
	}
	free(state->old_pwd);
	free(state->pwd);
	state->old_pwd = new_oldpwd;
	state->pwd = new_pwd;
	state->pwd_exec = (find_env_var(*env, "PWD") == NULL);
	state->oldpwd_exec = (find_env_var(*env, "OLDPWD") == NULL);
}
void 	ft_error(const char *path, t_error err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd((char *)path, 2);
	ft_putstr_fd(": ", 2);
	if (err == NO_FILE)
		ft_putendl_fd("No such file or directory", 2);
	if (err == NOT_DIR)
		ft_putendl_fd("Not a directory", 2);
	if (err == NO_PERM)
		ft_putendl_fd("Permission denied", 2);
	if (err == UNSET_HOME)
		ft_putendl_fd("HOME not set", 2);
}
int ft_cd(t_env **env, t_shell_state *state, char *path)
{
	char 			*oldpwd;
	char 			*pwd;
	t_error 		check;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (1);
	check = validate_directory(env, path);
	if (check != SUCSSES)
	{
		ft_error(path, check);
		free(oldpwd);
		return (1);
	}
	if (change_directory(path))
	{
		free(oldpwd);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	update_shell_state(env, state, oldpwd, pwd);
	if (find_env_var(*env, "OLDPWD"))
		update_env(env, "OLDPWD", oldpwd);
	if (find_env_var(*env, "PWD"))
		update_env(env, "PWD", pwd);
	free(oldpwd);
	free(pwd);
	return (0);
}


