/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahamdan <hahamdan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:12:16 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/25 13:59:21 by hahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_wait(t_mshell *mshell, pid_t pid, int *wstatus)
{
	if (waitpid(pid, wstatus, 0) == -1)
	{
		perror("minishell: waitpid");
		if (mshell->p_id)
		{
			free(mshell->p_id);
			mshell->p_id = NULL;
		}
		return (-1);
	}
	return (0);
}

static int	wait_process(t_mshell *mshell, pid_t p_id)
{
	int	wstatus;
	int	exit_status;

	wstatus = 0;
	exit_status = EXIT_SUCCESS;
	if (ft_wait(mshell, p_id, &wstatus) == -1)
		exit_status = EXIT_FAILURE;
	if (WIFEXITED(wstatus))
		exit_status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		exit_status = 128 + WTERMSIG(wstatus);
	else
		exit_status = EXIT_FAILURE;
	return (exit_status);
}

int	wait_all(t_mshell *mshell, int i)
{
	int	last_status;

	last_status = EXIT_SUCCESS;
	if (!mshell->p_id)
		return (EXIT_FAILURE);
	while (mshell->cmds && i < mshell->count_cmds)
	{
		last_status = wait_process(mshell, mshell->p_id[i]);
		if (last_status == -1)
			last_status = 1;
		i++;
	}
	if (last_status == 131)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	else if (last_status == 130)
		ft_putchar_fd('\n', STDOUT_FILENO);
	if (mshell->p_id)
	{
		free(mshell->p_id);
		mshell->p_id = NULL;
	}
	return (last_status);
}

int	execution_error(t_mshell *mshell, t_cmd *cmd, int status)
{
	ft_putstr_fd(cmd->cmd_name, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	cleanup_mshell(mshell);
	exit(status);
}
