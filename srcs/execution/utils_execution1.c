/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:52:05 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/06 16:28:10 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_builtin(t_cmd *cmd)
{
	if (cmd && (!cmd->cmd_name || !cmd->splitted_cmd))
		return (0);
	if (ft_strcmp(cmd->cmd_name, "env") == 0 || ft_strcmp(cmd->cmd_name,
			"pwd") == 0 || ft_strcmp(cmd->cmd_name, "export") == 0
		|| ft_strcmp(cmd->cmd_name, "cd") == 0 || ft_strcmp(cmd->cmd_name,
			"echo") == 0 || ft_strcmp(cmd->cmd_name, "exit") == 0
		|| ft_strcmp(cmd->cmd_name, "unset") == 0)
		return (1);
	return (0);
}

char	**convert_env(t_env *env, char ***copy_env)
{
	int	i;
	int	len;

	*copy_env = ft_calloc(env_size(env) + 1, sizeof(char *));
	if (!(*copy_env))
		return (NULL);
	i = 0;
	while (env[i].key != NULL)
	{
		len = ft_strlen(env[i].key) + ft_strlen(env[i].value) + 2;
		(*copy_env)[i] = ft_calloc(len, sizeof(char));
		if (!(*copy_env)[i])
		{
			ft_free_grid((void **)(*copy_env));
			return (NULL);
		}
		ft_strlcpy((*copy_env)[i], env[i].key, ft_strlen(env[i].key) + 1);
		ft_strlcat((*copy_env)[i], "=", len);
		ft_strlcat((*copy_env)[i], env[i].value, len);
		i++;
	}
	(*copy_env)[i] = NULL;
	return (*copy_env);
}

void	parent_process(t_mshell *mshell)
{
	close(mshell->pipe_fd[1]);
	if (mshell->prev_read_fd != STDIN_FILENO)
		close(mshell->prev_read_fd);
	mshell->prev_read_fd = mshell->pipe_fd[0];
}

void	update_env_underscore(t_mshell *mshell)
{
	int		i;
	char	*cmd_value;
	int		len;

	i = 0;
	len = ft_grid_rows(mshell->cmds[0].splitted_cmd);
	if (&mshell->cmds[0] && mshell->cmds[0].splitted_cmd && len > 0)
		cmd_value = ft_strdup(mshell->cmds[0].splitted_cmd[len - 1]);
	while (mshell->env[i].key != NULL)
	{
		if (ft_strcmp(mshell->env[i].key, "_") == 0)
		{
			if (mshell->env[i].value)
				free(mshell->env[i].value);
			mshell->env[i].value = cmd_value;
			return ;
		}
		i++;
	}
	free(cmd_value);
}

void	error_return_path(t_mshell *mshell, char *err_in, char *msg, int status)
{
	ft_putstr_fd("minishell: ", 2);
	if (*err_in != '\0')
		ft_putstr_fd(err_in, 2);
	if (*msg == '\0' || !msg)
	{
		ft_putstr_fd(": ", 2);
		perror("");
	}
	else
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	cleanup_mshell(mshell);
	exit(status);
}
