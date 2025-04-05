/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:12:16 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/05 16:47:08 by shachowd         ###   ########.fr       */
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
	setup_signal_handlers();
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
	int	child_status;
	int	last_status;

	child_status = EXIT_SUCCESS;
	last_status = EXIT_SUCCESS;
	if (!mshell->p_id)
		return (EXIT_FAILURE);
	while (mshell->cmds && i < mshell->count_cmds)
	{
		child_status = wait_process(mshell, mshell->p_id[i]);
		if (child_status == -1)
			child_status = 1;
		last_status = child_status;
		i++;
	}
	if (child_status == 131)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	if (mshell->p_id)
	{
		free(mshell->p_id);
		mshell->p_id = NULL;
	}
	return (last_status);
}
