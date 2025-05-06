/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:51:57 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/06 12:19:02 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_child_cmds(t_mshell *mshell, int i, int *status)
{
	if (allocate_pid(mshell) == -1)
		return (EXIT_FAILURE);
	while (mshell->cmds && i < mshell->count_cmds)
	{
		if (setup_pipe(mshell) == -1)
			return (EXIT_FAILURE);
		mshell->p_id[i] = fork();
		if (create_child_process(mshell, mshell->p_id[i]) == -1)
			return (EXIT_FAILURE);
		if (mshell->p_id[i] == 0)
		{
			setup_child_signals();
			child_process(mshell, i, status);
		}
		else
		{
			ignore_parent_signals();
			parent_process(mshell);
		}
		i++;
	}
	close_fds(mshell);
	*status = wait_all(mshell, 0);
	setup_signal_handlers();
	return (*status);
}

static int	store_std_fd(t_cmd *cmd, int *status)
{
	cmd->std_fd[0] = dup(STDIN_FILENO);
	if (cmd->std_fd[0] == -1)
	{
		ft_putstr_fd("minishell: STDIN setting failed\n", 2);
		*status = 1;
		return (EXIT_FAILURE);
	}
	cmd->std_fd[1] = dup(STDOUT_FILENO);
	if (cmd->std_fd[1] == -1)
	{
		ft_putstr_fd("minishell: STDOUT setting failed\n", 2);
		*status = 1;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	restore_std_fd(t_cmd *cmd, int *status)
{
	if (redirect_fd(cmd->std_fd[0], STDIN_FILENO) == EXIT_FAILURE)
	{
		ft_putstr_fd("minishell: STDIN resetting failed\n", 2);
		*status = 1;
		cmd->std_fd[0] = -1;
		return (EXIT_FAILURE);
	}
	cmd->std_fd[0] = -1;
	if (redirect_fd(cmd->std_fd[1], STDOUT_FILENO) == EXIT_FAILURE)
	{
		ft_putstr_fd("minishell: STDOUT resetting failed\n", 2);
		*status = 1;
		cmd->std_fd[1] = -1;
		return (EXIT_FAILURE);
	}
	cmd->std_fd[0] = -1;
	return (EXIT_SUCCESS);
}

static int	builtins_in_parent(t_mshell *mshell, t_cmd *cmd, int *status)
{
	int	len;

	len = get_rd_list_len(cmd->token);
	if (store_std_fd(cmd, status) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (redirect_handle_cmd(mshell, cmd, len) == EXIT_FAILURE)
	{
		*status = mshell->exit_code;
		restore_std_fd(cmd, status);
		return (EXIT_FAILURE);
	}
	if (execute_builtins(mshell, cmd, status) != EXIT_SUCCESS)
	{
		restore_std_fd(cmd, status);
		return (EXIT_FAILURE);
	}
	if (restore_std_fd(cmd, status) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	execute_cmds(t_mshell *mshell)
{
	int	status;

	status = mshell->exit_code;
	if (!mshell->cmds || mshell->count_cmds == 0)
		return ;
	g_store_sigint = 0;
	heredoc_handle(mshell, &status);
	if (interrupt_input(mshell))
		return ;
	if (check_is_builtin(&mshell->cmds[0]) && mshell->count_cmds == 1)
	{
		update_env_underscore(mshell);
		if (builtins_in_parent(mshell, &mshell->cmds[0],
				&status) == EXIT_FAILURE)
		{
			mshell->exit_code = status;
			return ;
		}
	}
	else
		execute_child_cmds(mshell, 0, &status);
	mshell->exit_code = status;
}
