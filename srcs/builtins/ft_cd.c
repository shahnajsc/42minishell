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
			return ;
		}
		j++;
	}
}

int ft_cd(t_env **env, char *path)
{
	char 	*oldpwd;
	char 	*newpwd;
	char 	*home;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (1);
	if (!path)
	{
		home = getenv("HOME");
		if (!home)
		{
			printf("cd: HOME not set\n");
			free(oldpwd);
			return (1);
		}
		path = home;
	}
	if (chdir(path))
	{
		printf("chdir error");
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
