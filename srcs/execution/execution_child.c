#include "minishell.h"

void 	 external_in_child(t_mshell *mshell, t_cmd *cmd, char ***copy_env)
{
	char *cmd_path;
	int len;

	cmd->std_fd[0] = dup(STDIN_FILENO);
	cmd->std_fd[1] = dup(STDOUT_FILENO);
	len = get_rd_list_len(cmd->token);
	if (redirect_handle_cmd(mshell, cmd, len) == EXIT_FAILURE)
	{
		redirect_fd(cmd->std_fd[0], STDIN_FILENO);
		redirect_fd(cmd->std_fd[1], STDOUT_FILENO);
		return ;
	}
	cmd_path = get_command_path(mshell, cmd);
	if (!cmd_path || !*cmd_path)
	{
		redirect_fd(cmd->std_fd[0], STDIN_FILENO);
		redirect_fd(cmd->std_fd[1], STDOUT_FILENO);
		ft_putstr_fd(cmd->cmd_name, STDERR_FILENO);
		ft_putstr_fd(": [funct: external_in_child]command not found\n", STDERR_FILENO);
		ft_free_grid((void **)*copy_env);
		cleanup_mshell(mshell);
		mshell->exit_code = 127;
		exit(mshell->exit_code);
	}
	printf("no cmd-path\n");
	execve(cmd_path, cmd->splitted_cmd, *copy_env);
	perror("minishell");
	ft_free_grid((void **)*copy_env);
	cleanup_mshell(mshell);
	free(cmd_path);
	redirect_fd(cmd->std_fd[0], STDIN_FILENO);
	redirect_fd(cmd->std_fd[1], STDOUT_FILENO);
	exit (EXIT_FAILURE);
}

int	builtins_in_child(t_mshell *mshell, t_cmd *cmd, int *status)
{
	int len;

	cmd->std_fd[0] = dup(STDIN_FILENO);
	cmd->std_fd[1] = dup(STDOUT_FILENO);
	len = get_rd_list_len(cmd->token);
	if (redirect_handle_cmd(mshell, cmd, len) == EXIT_FAILURE)
	{
		redirect_fd(cmd->std_fd[0], STDIN_FILENO);
		redirect_fd(cmd->std_fd[1], STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	if (execute_builtins(mshell, cmd,status) > 0 )
	{
		redirect_fd(cmd->std_fd[0], STDIN_FILENO);
		redirect_fd(cmd->std_fd[1], STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	redirect_fd(cmd->std_fd[0], STDIN_FILENO);
	redirect_fd(cmd->std_fd[1], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int  check_command_exec(t_mshell *mshell, int i, int *status)
{
    char 	**copy_env;

	copy_env = NULL;
    if (check_is_builtin(&mshell->cmds[i]))
    {
		if (builtins_in_child(mshell, &mshell->cmds[i], status) > 0)
		{
			cleanup_mshell(mshell);
			exit(*status);
		}
		cleanup_mshell(mshell);
    }
    else
    {
        convert_env(mshell->env, &copy_env);
        external_in_child(mshell, &mshell->cmds[i], &copy_env);
    }
	exit(254);
}

void	child_process(t_mshell *mshell, int i, int *status)
{
    close(mshell->pipe_fd[0]);
    if (mshell->prev_read_fd != STDIN_FILENO)
        redirect_fd(mshell->prev_read_fd, STDIN_FILENO);
    if (i < mshell->count_cmds - 1)
		redirect_fd(mshell->pipe_fd[1], STDOUT_FILENO);
	else
		close(mshell->pipe_fd[1]);
	check_command_exec(mshell, i, status);
}

void	parent_process(t_mshell *mshell)
{
	close(mshell->pipe_fd[1]);
    if (mshell->prev_read_fd != STDIN_FILENO)
		close(mshell->prev_read_fd);
    mshell->prev_read_fd = mshell->pipe_fd[0];
}
