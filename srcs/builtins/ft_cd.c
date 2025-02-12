#include <minishell.h>

void 	update_env(t_env **env, const char *key, const char *set_value)
{
	int 	i;
	int 	j;
	char 	*temp;

	i = 0;
	while ((*env)[i].key != NULL)
		i++;
	j = 0;
	while (j < i)
	{
		if (ft_strcmp((*env)[j].key, (char *)key) == 0)
		{
			temp = ft_strdup(set_value);
			if (!temp)
			{
				printf("allocation failed\n");
				return ;
			}
			free((*env)[j].value);
			(*env)[j].value = temp;
			// free(temp);
			return ;
		}
		j++;
	}
}

int 	check_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("No such file or directory", 2);
        return (0);
	}
	if (S_ISDIR(path_stat.st_mode))
        return (1);
	ft_putstr_fd("bash: ", 2);
    ft_putstr_fd("cd: ", 2);
    ft_putstr_fd((char *)path, 2);
    ft_putstr_fd(": Not a directory", 2);
    ft_putendl_fd("", 2);
	return (0);
}

int 	home_directory(t_env **env, char **path)
{
	char 	*home;
	int 	i;

	if (!*path)
	{
		i = 0;
		while ((*env)[i].key != NULL)
		{
			if (ft_strcmp((*env)[i].key, "HOME") == 0)
				home = (*env)[i].value;
			i++;
		}
		if (!home)
			return (1);
		*path = home;
	}
	return (0);
}

int change_directory(const char *path)
{
    if (chdir(path) != 0)
    {
        ft_putstr_fd("bash: cd: ", 2);
        ft_putstr_fd((char *)path, 2);
        ft_putstr_fd(": ", 2);
        if (errno == ENOENT)   // Handle different errors based on errno
            ft_putendl_fd("No such file or directory", 2);
        else if (errno == EACCES)
            ft_putendl_fd("Permission denied", 2);
        else if (errno == ENOTDIR)
            ft_putendl_fd("Not a directory", 2);
        else
            ft_putendl_fd(strerror(errno), 2); // Other errors
        return (1);
    }
    return (0); 
}

int ft_cd(t_env **env, char *path)
{
	char 	*oldpwd;
	char 	*newpwd;

	if (home_directory(env, &path))
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (1);
	if (!check_directory(path))
	{
		free(oldpwd);
		return (1);
	}
	if (change_directory(path))
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
