/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:40:55 by shachowd          #+#    #+#             */
/*   Updated: 2025/01/31 17:39:43 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipe_init(t_pipex *data)
{
	int	i;

	i = 0;
	while (data->fd && i < (data->argc - 3 - data->here_doc))
	{
		if (pipe(data->fd[i]) == -1)
		{
			close_fds(data);
			error_return(data, "pipe()", "", 1);
		}
		i++;
	}
}

int	get_file_fd(t_pipex *data, int i, char *filename)
{
	int	file_fd;

	file_fd = 0;
	if (i == 0)
	{
		filename = data->argv[1];
		if (access(filename, F_OK) == 0 && access(filename, R_OK) == -1)
			error_return(data, filename, "", 1);
		file_fd = open(filename, O_RDONLY, 0444);
	}
	else
	{
		filename = data->argv[data->argc - 1];
		if (access(filename, F_OK) == 0 && access(filename, W_OK) == -1)
			error_return(data, filename, "", 1);
		if (data->here_doc)
			file_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			file_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (file_fd == -1)
		error_return(data, filename, "", 1);
	return (file_fd);
}

void	redirect_fd(t_pipex *data, int infd, int outfd)
{
	if (dup2(infd, STDIN_FILENO) == -1)
		error_return(data, "dup2()", "", 1);
	if (dup2(outfd, STDOUT_FILENO) == -1)
		error_return(data, "dup2", "", 1);
	close(infd);
	close(outfd);
}

int	wait_process(pid_t pid)
{
	int	wstatus;

	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	return (1);
}
