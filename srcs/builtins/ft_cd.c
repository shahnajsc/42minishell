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
				return (1);
			}
			free((*env)[j].value);
			(*env)[j].value = temp;
			return ;
		}
		j++;
	}
}

void 	cd_error(const char *path, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd((char *)path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
}
int 	check_permissions(const char *path)
{
	if (access(path, W_OK) != 0 || access(path, X_OK) != 0 || access(path, R_OK) != 0)
		return (1);  // minishell: cd: test/: Permission denied
	return (0);
}
int 	check_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (1);   // minishell: cd: hello: No such file or directory
	if (!S_ISDIR(path_stat.st_mode))
		return (1);  // minishell: cd: includes/minishell.h: Not a directory
	return (check_permissions(path));
}

int 	home_directory(t_env **env, char **path)
{
	char 	*home;
	int 	i;

	home = NULL;
	if (!*path)
	{
		i = 0;
		while ((*env)[i].key != NULL)
		{
			if (ft_strcmp((*env)[i].key, "HOME") == 0)
			{	
				home = (*env)[i].value;
				break;
			}
			i++;
		}
		if (!home)
			return (1);  // minishell: cd: HOME not set
		*path = home;
	}
	return (0);
}

int change_directory(const char *path)
{
    if (chdir(path) != 0)
        return (1);
    return (0); 
}
// int	builtin_err_print(t_mshell *mshell, char *err_msg, char *cmd)
// {
// 	ft_putstr_fd("minishell: ", 2);
// 	if (err_msg)
// 		ft_putstr_fd(err_msg, 2);
// 	if (cmd)
// 		ft_putstr_fd(cmd, 2);
	
// 	mshell->exit_code = 1;
// 	return (1);
// }

int ft_cd(t_env **env, char *path)
{
	char 	*oldpwd;
	char 	*newpwd;

	if (home_directory(env, &path))
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (1);
		
	if (check_directory(path))
	{
		free(oldpwd);
		return (1);
		// return (builtin_err_print(mshell, "not a directory", path)); //after paring
	}
	if (chdir(path) != 0)
	{
		free(oldpwd);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return (1);
	
	update_env(env, "OLDPWD", oldpwd);
	update_env(env, "PWD", newpwd);
	free(oldpwd);
	free(newpwd);
	return (0);
}
