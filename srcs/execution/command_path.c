/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:51:30 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/05 16:46:45 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_envp_paths(t_mshell *mshell, int i)
{
	char	**env_paths;

	if (!mshell->env)
		return (NULL);
	while (mshell->env && mshell->env[++i].key)
	{
		if (ft_strcmp(mshell->env[i].key, "PATH") == 0)
		{
			env_paths = ft_split(mshell->env[i].value, ':');
			if (!env_paths)
				error_return_path(mshell, "ft_split()", "", 1);
			return (env_paths);
		}
	}
	env_paths = (char **)ft_calloc(2, sizeof(char *));
	if (!env_paths)
		error_return_path(mshell, "ft_split()", "", 1);
	env_paths[0] = getcwd(NULL, 0);
	if (!env_paths[0])
	{
		ft_free_grid((void **)env_paths);
		error_return_path(mshell, "getcwd()", "", 1);
	}
	mshell->flag_path = 1;
	return (env_paths);
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
		if (!final_path)
			return (NULL);
		if (access(final_path, F_OK) == 0)
			return (final_path);
		free(final_path);
		i++;
	}
	return (NULL);
}

static int	validate_command(t_mshell *mshell, t_cmd *cmd)
{
	struct stat	sb;

	if (stat(cmd->cmd_name, &sb) == -1)
		clean_and_exit(mshell, ": No such file or directory\n", 127);
	if (S_ISDIR(sb.st_mode))
		clean_and_exit(mshell, ": Is a directory\n", 126);
	if ((sb.st_mode & (S_IRUSR | S_IRGRP)) == 0
		|| (sb.st_mode & (S_IWUSR | S_IWGRP)) == 0
		|| (sb.st_mode & (S_IXUSR | S_IXGRP)) == 0)
		clean_and_exit(mshell, ": Permission denied\n", 126);
	return (EXIT_SUCCESS);
}

char	*get_command_path(t_mshell *mshell, t_cmd *cmd)
{
	char	*cmd_path;
	char	**env_paths;

	if (cmd->cmd_name && ft_strchr(cmd->cmd_name, '/'))
	{
		if (validate_command(mshell, cmd) == EXIT_SUCCESS)
			return (cmd->cmd_name);
	}
	env_paths = get_envp_paths(mshell, -1);
	cmd_path = get_path_cmd(env_paths, cmd->cmd_name);
	if (mshell->flag_path && !cmd_path)
	{
		ft_free_grid((void **)env_paths);
		clean_and_exit(mshell, ": No such file or directory\n", 127);
	}
	ft_free_grid((void **)env_paths);
	return (cmd_path);
}
