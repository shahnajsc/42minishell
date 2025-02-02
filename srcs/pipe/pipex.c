/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:40:25 by shachowd          #+#    #+#             */
/*   Updated: 2025/01/31 17:39:37 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	first_process(t_pipex *data, int i, int infd, int outfd)
{
	infd = get_file_fd(data, 0, data->argv[1]);
	outfd = data->fd[i][1];
	close(data->fd[i][0]);
	redirect_fd(data, infd, outfd);
	close_fds(data);
	execve_init(data, data->argv[i + 2 + data->here_doc]);
}

static void	middle_process(t_pipex *data, int i, int infd, int outfd)
{
	infd = data->fd[i - 1][0];
	outfd = data->fd[i][1];
	close(data->fd[i][0]);
	redirect_fd(data, infd, outfd);
	close_fds(data);
	execve_init(data, data->argv[i + 2 + data->here_doc]);
}

static void	last_process(t_pipex *data, int i, int infd, int outfd)
{
	infd = data->fd[i - 1][0];
	outfd = get_file_fd(data, 1, data->argv[data->argc - 1]);
	close(data->fd[i][1]);
	redirect_fd(data, infd, outfd);
	close_fds(data);
	execve_init(data, data->argv[i + 2 + data->here_doc]);
}

static void	handle_proces(t_pipex *data, int i)
{
	int	infd;
	int	outfd;

	infd = 0;
	outfd = 0;
	if (i == 0)
		first_process(data, i, infd, outfd);
	else if (i == (data->argc - 3 - data->here_doc - 1))
		last_process(data, i, infd, outfd);
	else
		middle_process(data, i, infd, outfd);
	close(infd);
	close(outfd);
	close_fds(data);
	exit(EXIT_SUCCESS);
}

int	pipex(t_pipex *data)
{
	int	pipe_status;
	int	i;

	data->p_id = (int *)malloc((data->argc - 3 - data->here_doc) * sizeof(int));
	if (!data->p_id)
		error_return(data, "malloc()", "", 1);
	if (data->here_doc && data->argc >= 6)
		read_here_doc(data);
	pipe_init(data);
	i = -1;
	while (++i < (data->argc - 3 - data->here_doc))
	{
		data->p_id[i] = fork();
		if (data->p_id[i] == -1)
			error_return(data, "fork()", "", 1);
		if (data->p_id[i] == 0)
			handle_proces(data, i);
	}
	close_fds(data);
	i = -1;
	while (++i < (data->argc - 3 - data->here_doc))
	{
		pipe_status = wait_process(data->p_id[i]);
	}
	return (pipe_status);
}
