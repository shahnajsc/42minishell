#include "minishell.h"

int  wait_all(t_mshell *mshell)
{
    int i;
    int child_status;
    int last_status;

    i = 0;
	child_status = 0;
	last_status = 0;
    while (mshell->cmds && i < mshell->count_cmds)
    {
        child_status = wait_process(mshell, mshell->p_id[i]);
        if (child_status == -1)
            child_status = 1;
        last_status = child_status;
        i++;
    }
	if (mshell->p_id)
	{
		free(mshell->p_id);
		mshell->p_id =  NULL;
	}
    return (last_status);
}

int execute_child_cmds(t_mshell *mshell, int i, int *status)
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
            child_process(mshell, i, status);
        else
            parent_process(mshell);
        i++;
    }
    close_fds(mshell);
    *status = wait_all(mshell);
    return (*status);
}
int	builtins_in_parent(t_mshell *mshell, t_cmd *cmd, int *status)
{
	int len;

	cmd->i_o_fd[0] = dup(STDIN_FILENO);
	cmd->i_o_fd[1] = dup(STDOUT_FILENO);
	len = get_rd_list_len(cmd->token);
	if (redirect_handle_cmd(mshell, cmd, len) == EXIT_FAILURE)
	{
		redirect_fd(cmd->i_o_fd[0], STDIN_FILENO);
		redirect_fd(cmd->i_o_fd[1], STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	if (execute_builtins(mshell, cmd,status) > 0 )
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
	int 	status;

	if (!mshell->cmds || mshell->count_cmds == 0)
		return ;
	if (heredoc_handle(mshell) == EXIT_FAILURE)
		return ;
	if (check_is_builtin(&mshell->cmds[0]) && mshell->count_cmds == 1)
	{
		if (builtins_in_parent(mshell, &mshell->cmds[0], &status) == EXIT_FAILURE)
			return ;
	}
	else
		execute_child_cmds(mshell, 0, &status);
	mshell->exit_code = status;
	printf("status: %d\n", status);
}
