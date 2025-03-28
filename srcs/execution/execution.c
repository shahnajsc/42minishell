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
    return (EXIT_SUCCESS);
}

int	store_std_fd(t_mshell *mshell, t_cmd *cmd, int *status)
{
	// if (cmd->redi_fd[0] != -1 && cmd->redi_fd[0] != -2)
	// {
	// 	cmd->std_fd[0] = dup(STDIN_FILENO);
	// 	if (cmd->std_fd[0] == -1)
	// 	{
	// 		ft_putstr_fd("minishell: STDIN setting failed\n", 2);
	// 		mshell->exit_code = 1;
	// 		return (EXIT_FAILURE);
	// 	}
	// }
	// if (cmd->redi_fd[1] != -1 && cmd->redi_fd[1] != -2)
	// {
	// 	cmd->std_fd[1] = dup(STDOUT_FILENO);
	// 	if (cmd->std_fd[1] == -1)
	// 	{
	// 		ft_putstr_fd("minishell: STDOUT setting failed\n", 2);
	// 		mshell->exit_code = 1;
	// 		return (EXIT_FAILURE);
	// 	}
	// }
	// return (EXIT_SUCCESS);
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
		mshell->exit_code = *status;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	restore_std_fd(t_mshell *mshell, t_cmd *cmd, int *status)
{
	// if (cmd->std_fd[0] != -1)
	// {
	// 	if(redirect_fd(cmd->std_fd[0], STDIN_FILENO) == EXIT_FAILURE)
	// 	{
	// 		ft_putstr_fd("minishell: STDIN resetting failed\n", 2);
	// 		mshell->exit_code = 1;
	// 		cmd->std_fd[0]  = -1;
	// 		return (EXIT_FAILURE);
	// 	}
	// 	cmd->std_fd[0]  = -1;
	// }
	// if (cmd->std_fd[1] != -1)
	// {
	// 	if(redirect_fd(cmd->std_fd[1], STDOUT_FILENO) == EXIT_FAILURE)
	// 	{
	// 		ft_putstr_fd("minishell: STDOUT resetting failed\n", 2);
	// 		mshell->exit_code = 1;
	// 		cmd->std_fd[1]  = -1;
	// 		return (EXIT_FAILURE);
	// 	}
	// 	cmd->std_fd[0]  = -1;
	// }
	// return (EXIT_SUCCESS);
	if(redirect_fd(cmd->std_fd[0], STDIN_FILENO) == EXIT_FAILURE)
	{
		ft_putstr_fd("minishell: STDIN resetting failed\n", 2);
		*status = 1;
		cmd->std_fd[0]  = -1;
		return (EXIT_FAILURE);
	}
	cmd->std_fd[0]  = -1;
	if(redirect_fd(cmd->std_fd[1], STDOUT_FILENO) == EXIT_FAILURE)
	{
		ft_putstr_fd("minishell: STDOUT resetting failed\n", 2);
		*status = 1;
		cmd->std_fd[1]  = -1;
		mshell->exit_code = *status;
		return (EXIT_FAILURE);
	}
	cmd->std_fd[0]  = -1;
	return (EXIT_SUCCESS);
}
int	builtins_in_parent(t_mshell *mshell, t_cmd *cmd, int *status)
{
	int len;

	len = get_rd_list_len(cmd->token);
	if (store_std_fd(mshell, cmd, status) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (redirect_handle_cmd(mshell, cmd, len) == EXIT_FAILURE)
	{
		restore_std_fd(mshell, cmd, status);
		return (EXIT_FAILURE);
	}
	if (execute_builtins(mshell, cmd,status) > 0 )
	{
		restore_std_fd(mshell, cmd, status);
		return (EXIT_FAILURE);
	}
	if (restore_std_fd(mshell, cmd, status) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
	// int len;

	// cmd->std_fd[0] = dup(STDIN_FILENO);
	// cmd->std_fd[1] = dup(STDOUT_FILENO);
	// len = get_rd_list_len(cmd->token);
	// if (redirect_handle_cmd(mshell, cmd, len) == EXIT_FAILURE)
	// {
	// 	redirect_fd(cmd->std_fd[0], STDIN_FILENO);
	// 	redirect_fd(cmd->std_fd[1], STDOUT_FILENO);
	// 	return (EXIT_FAILURE);
	// }
	// if (execute_builtins(mshell, cmd,status) > 0 )
	// {
	// 	redirect_fd(cmd->std_fd[0], STDIN_FILENO);
	// 	redirect_fd(cmd->std_fd[1], STDOUT_FILENO);
	// 	return (EXIT_FAILURE);
	// }
	// redirect_fd(cmd->std_fd[0], STDIN_FILENO);
	// redirect_fd(cmd->std_fd[1], STDOUT_FILENO);
	// return (EXIT_SUCCESS);
}

void	execute_cmds(t_mshell *mshell)
{
	int 	status;

	//status = mshell->exit_code;
	if (!mshell->cmds || mshell->count_cmds == 0)
		return ;
	if (heredoc_handle(mshell) == EXIT_FAILURE)
		return ;
	if (check_is_builtin(&mshell->cmds[0]) && mshell->count_cmds == 1)
	{
		if (builtins_in_parent(mshell, &mshell->cmds[0], &status) == EXIT_FAILURE)
		{
			mshell->exit_code = status;
			return ;
		}
	}
	else
		execute_child_cmds(mshell, 0, &status);
	mshell->exit_code = status;
	//printf("status: %d\n", status);
}

