#include "minishell.h"

static char	**get_envp_paths(t_mshell *mshell)
{
	char	**env_paths;
	int		i;

	if (!mshell->env)
		return (NULL);
	i = 0;
	while (mshell->env && mshell->env->key)
	{
		if (ft_strcmp(mshell->env[i].key, "PATH") == 0)
		{
			env_paths = ft_split(mshell->env[i].value, ':');
			if (!env_paths)
				error_return(mshell, "ft_split()", "", 1);
			return (env_paths);
		}
		i++;
	}
	return (NULL);
}

static char	*combine_path_cmd(char *env_path, char *cmd_name)
{
	char	*combined_path;
	int		len_env;
	int		len_cmd;

	len_env = ft_strlen(env_path);
	len_cmd = ft_strlen(cmd_name);
	combined_path = (char *)malloc(sizeof(char) * (len_env + len_cmd + 2));
	if (!combined_path)
		return (NULL);
	ft_strlcpy(combined_path, env_path, len_env + 1);
	ft_strlcpy(combined_path + len_env, "/", 2);
	ft_strlcpy(combined_path + len_env + 1, cmd_name, len_cmd + 1);
	return (combined_path);
}

static char	*get_path_cmd(char **env_paths, char *cmd_name)
{
	char	*final_path;
	int		i;

	i = 0;
	while (env_paths[i] != NULL)
	{
		final_path = combine_path_cmd(env_paths[i], cmd_name);
		if (!final_path || access(final_path, F_OK) == 0)
			return (final_path);
		free(final_path);
		i++;
	}
	return (NULL);
}

char	*get_command_path(t_mshell *mshell, t_cmd *cmd)
{
	char	*cmd_path;
	char	**env_paths;

	if (ft_strchr(cmd->cmd_name, '/'))
	{
		if (access(cmd->cmd_name, F_OK) == 0)
			return (cmd->cmd_name);
		else
			error_return(mshell, cmd->cmd_name, "", 127);
	}
	env_paths = get_envp_paths(mshell);
	if (!env_paths)
		error_return(mshell, cmd->cmd_name, "No such file or directory", 127);
	cmd_path = get_path_cmd(env_paths, cmd->cmd_name);
	return (cmd_path);
}
