/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:12:16 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/02 17:07:50 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process(t_mshell *mshell)
{
	close(mshell->pipe_fd[1]);
	if (mshell->prev_read_fd != STDIN_FILENO)
		close(mshell->prev_read_fd);
	mshell->prev_read_fd = mshell->pipe_fd[0];
}

int	wait_all(t_mshell *mshell, int i)
{
	int	child_status;
	int	last_status;

	child_status = 0;
	last_status = 0;
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
