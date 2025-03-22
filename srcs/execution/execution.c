#include "minishell.h"

int	check_is_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd_name, "env") == 0
		|| ft_strcmp(cmd->cmd_name, "pwd") == 0
		|| ft_strcmp(cmd->cmd_name, "export") == 0
		|| ft_strcmp(cmd->cmd_name, "cd") == 0
		|| ft_strcmp(cmd->cmd_name, "echo") == 0
		|| ft_strcmp(cmd->cmd_name, "exit") == 0
		|| ft_strcmp(cmd->cmd_name, "unset") == 0)
		return (1);
	return (0);
}

int	execute_child_cmds(t_mshell *mshell)
{
	int			i;
	pid_t 		p_id;
	int 		pipe_fd[2];

	i = 0;
	while (mshell->cmds && i < mshell->count_cmds)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("Error");
			return (EXIT_FAILURE);
		}
		p_id = fork();
		if (p_id == -1)
		{
			perror("Error");
			return (EXIT_FAILURE);
		}
		if (p_id == 0)
			call_child_process(mshell, pipe_fd, i);
		else
			call_parent_process(mshell, pipe_fd, i);
		wait_processes(p_id);
		i++;
		// close(pipe_fd[0]);
		// close(pipe_fd[1]);
		// if (mshell->prev_read_fd)
		// 	close(mshell->prev_read_fd);
	}
	// wait_processes(mshell);
	 if (mshell->prev_read_fd != STDIN_FILENO)
        close(mshell->prev_read_fd);
	 mshell->prev_read_fd = STDIN_FILENO;
	return (EXIT_SUCCESS);
}

int	builtins_in_parent(t_mshell *mshell, t_cmd *cmd)
{
	cmd->i_o_fd[0] = dup(STDIN_FILENO);
	cmd->i_o_fd[1] = dup(STDOUT_FILENO);

	int len;

	len = get_rd_list_len(cmd->token);
	if (redirect_handle_cmd(mshell, cmd, len) == EXIT_FAILURE)
	{
		redirect_fd(cmd->i_o_fd[0], STDIN_FILENO);
		redirect_fd(cmd->i_o_fd[1], STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	if (execute_builtins(mshell, cmd) > 0 )
	{
		redirect_fd(cmd->i_o_fd[0], STDIN_FILENO);
		redirect_fd(cmd->i_o_fd[1], STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	redirect_fd(cmd->i_o_fd[0], STDIN_FILENO);
	redirect_fd(cmd->i_o_fd[1], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

void	execute_cmds(t_mshell *mshell)
{
	if (!mshell->cmds || mshell->count_cmds == 0)
		return ;
	if (check_is_builtin(&mshell->cmds[0]) && mshell->count_cmds == 1)
	{
		if (builtins_in_parent(mshell, &mshell->cmds[0]) == EXIT_FAILURE)
			return ;
		mshell->exit_code = 0;
	}
	else
	{
		if (execute_child_cmds(mshell) == EXIT_FAILURE)
			return ;
	}
}

