/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:55:15 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/05 15:54:15 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_heredoc_fd(t_mshell *mshell, t_redirect *rd_list, int i)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (file_error(mshell, NULL, "Pipe open failed", 1));
	}
	ft_putstr_fd(rd_list[i].hd_lines, pipe_fd[1]);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	get_file_fd(t_mshell *mshell, char *path, t_redirect_type rd_type)
{
	int	file_fd;

	file_fd = -2;
	if (rd_type == RD_IN)
		file_fd = open(path, O_RDONLY, 0444);
	else
	{
		if (rd_type == RD_APPEND)
			file_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (rd_type == RD_OUT)
			file_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (file_fd == -1)
		return (file_error(mshell, path, strerror(errno), 1));
	return (file_fd);
}
