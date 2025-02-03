/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:38:28 by shachowd          #+#    #+#             */
/*   Updated: 2025/01/31 17:39:07 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	error_handle_execv(t_pipex *data, char *cmd)
{
	if (ft_strchr(cmd, '/') && !access(cmd, X_OK))
		error_return(data, cmd, "Is a directory", 126);
	else if (!ft_strchr(cmd, '/') && !access(cmd, X_OK))
		error_return(data, cmd, "command not found", 127);
	else if (access(cmd, X_OK) == -1 && !ft_strchr(cmd, '/'))
		error_return(data, data->cmd_path, "", 126);
	else
		error_return(data, cmd, "", 126);
}

void	execve_init(t_pipex *data, char *cmd)
{
	split_command(data, cmd);
	if (!data->sp_cmd)
		error_return(data, cmd, "", 127);
	data->cmd_path = get_command_path(data);
	if (!data->cmd_path)
		error_return(data, cmd, "command not found", 127);
	execve(data->cmd_path, data->sp_cmd, data->envp);
	error_handle_execv(data, cmd);
}
