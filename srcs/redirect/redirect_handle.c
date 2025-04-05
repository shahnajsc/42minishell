/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:55:23 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/05 15:54:36 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_fd(int from_fd, int to_fd)
{
	if (dup2(from_fd, to_fd) == -1)
	{
		close(from_fd);
		perror("minishell: dup2");
		return (EXIT_FAILURE);
	}
	close(from_fd);
	return (EXIT_SUCCESS);
}

static int	set_rd_fds(t_mshell *mshell, t_cmd *cmd, int new_in_fd,
		int new_out_fd)
{
	if (new_in_fd != -2)
	{
		if (cmd->redi_fd[0] != -1 && cmd->redi_fd[0] != -2)
			close(cmd->redi_fd[0]);
		cmd->redi_fd[0] = new_in_fd;
	}
	if (new_out_fd != -2)
	{
		if (cmd->redi_fd[1] != -1 && cmd->redi_fd[1] != -2)
			close(cmd->redi_fd[1]);
		cmd->redi_fd[1] = new_out_fd;
	}
	if (new_in_fd == -1 || new_out_fd == -1)
	{
		mshell->exit_code = 1;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	rd_fd_redirect(t_cmd *cmd)
{
	if (cmd->redi_fd[0] != -1 && cmd->redi_fd[0] != -2)
	{
		if (redirect_fd(cmd->redi_fd[0], STDIN_FILENO) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (cmd->redi_fd[1] != -1 && cmd->redi_fd[1] != -2)
	{
		if (redirect_fd(cmd->redi_fd[1], STDOUT_FILENO) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	redirect_handle_cmd(t_mshell *mshell, t_cmd *cmd, int len)
{
	int			i;
	t_redirect	*rds;
	int			fd[2];

	i = 0;
	rds = cmd->redirects;
	while (cmd->redirects && i < len)
	{
		fd[0] = -2;
		fd[1] = -2;
		if (rds[i].rd_type == RD_HEREDOC)
			fd[0] = get_heredoc_fd(mshell, rds, i);
		else if (rds[i].rd_type == RD_IN)
			fd[0] = get_file_fd(mshell, rds[i].file_deli, rds[i].rd_type);
		else if (rds[i].rd_type == RD_OUT)
			fd[1] = get_file_fd(mshell, rds[i].file_deli, rds[i].rd_type);
		else if (rds[i].rd_type == RD_APPEND)
			fd[1] = get_file_fd(mshell, rds[i].file_deli, rds[i].rd_type);
		if (set_rd_fds(mshell, cmd, fd[0], fd[1]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	if (rd_fd_redirect(cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
