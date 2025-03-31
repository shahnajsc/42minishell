#include "minishell.h"

int	external_in_child(t_mshell *mshell, t_cmd *cmd, char ***copy_env)
{
	char *cmd_path;

	if (!*cmd->cmd_name && cmd->redirects)
		clean_and_exit(mshell, copy_env, NULL, 0);
    if (ft_strcmp(cmd->cmd_name, ".") == 0)
    {   clean_and_exit(mshell, copy_env, ": filename argument required\n", 2);}
	cmd_path = get_command_path(mshell, cmd, copy_env);
	if (!cmd_path || ft_strcmp(cmd->cmd_name, "..") == 0)
	{
		ft_putstr_fd(cmd->cmd_name, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		ft_free_grid((void **)*copy_env);
		cleanup_mshell(mshell);
		mshell->exit_code = 127;
		exit(mshell->exit_code);
	}
	execve(cmd_path, cmd->splitted_cmd, *copy_env);
    {
        perror("minishell: execve");
        free(cmd_path);
        clean_and_exit(mshell, copy_env, NULL, EXIT_FAILURE);
    }
	return (0);
}

int	builtins_in_child(t_mshell *mshell, t_cmd *cmd, int *status)
{
	if (execute_builtins(mshell, cmd,status) != EXIT_SUCCESS )
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int  check_command_exec(t_mshell *mshell, int i, int *status)
{
    char 	**copy_env;

    copy_env = NULL;
	if (check_is_builtin(&mshell->cmds[i]))
    {
		if (builtins_in_child(mshell, &mshell->cmds[i], status) == EXIT_FAILURE)
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
	exit(EXIT_SUCCESS);
}

void	child_process(t_mshell *mshell, int i, int *status)
{
    int len;

	len = get_rd_list_len(mshell->cmds[i].token);
	close(mshell->pipe_fd[0]);
    if (mshell->prev_read_fd != STDIN_FILENO)
        redirect_fd(mshell->prev_read_fd, STDIN_FILENO);
    if (i < mshell->count_cmds - 1)
		redirect_fd(mshell->pipe_fd[1], STDOUT_FILENO);
	else
		close(mshell->pipe_fd[1]);
	if (redirect_handle_cmd(mshell, &mshell->cmds[i], len) == EXIT_FAILURE)
	{
		*status = mshell->exit_code;
		cleanup_mshell(mshell);
		exit(EXIT_FAILURE);
	}
	check_command_exec(mshell, i, status);
}

void	parent_process(t_mshell *mshell)
{
	close(mshell->pipe_fd[1]);
    if (mshell->prev_read_fd != STDIN_FILENO)
		close(mshell->prev_read_fd);
    mshell->prev_read_fd = mshell->pipe_fd[0];
}
