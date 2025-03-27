#include "minishell.h"

void 	 execute_external(t_mshell *mshell, t_cmd *cmd, char ***copy_env)
{
	char *cmd_path;

	cmd_path = get_command_path(mshell, cmd);
	if (!cmd_path)
	{
		ft_putstr_fd(cmd->cmd_name, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		ft_free_grid((void **)*copy_env);
		cleanup_mshell(mshell);
		exit(127);
	}
	execve(cmd_path, cmd->splitted_cmd, *copy_env);
	perror("minishell");
	ft_free_grid((void **)*copy_env);
	cleanup_mshell(mshell);
	free(cmd_path);
	exit (EXIT_FAILURE);
}

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
        mshell->p_id = NULL;
    }
    return (last_status);
}

int  check_command_exec(t_mshell *mshell, int i, int *status)
{
    char 	**copy_env;

	copy_env = NULL;
    if (check_is_builtin(&mshell->cmds[i]))
    {
		execute_builtins(mshell, &mshell->cmds[i], status);
		if (status != SUCSSES)
		{
			cleanup_mshell(mshell);
			exit(*status);
		}
		else
			cleanup_mshell(mshell);
    }
    else
    {
        convert_env(mshell->env, &copy_env);
        execute_external(mshell, &mshell->cmds[i], &copy_env);
    }
	exit(EXIT_SUCCESS);
}

int handle_pipeline(t_mshell *mshell, int i, int *status)
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
            child_redirection(mshell, i, status);
        else
            parent_redirecton(mshell);
        i++;
    }
    close_fds(mshell);
    *status = wait_all(mshell);
    return (*status);
}

void    handle_command_execution(t_mshell *mshell)
{
	int 	status;

    if (!mshell->cmds || mshell->count_cmds == 0)
    {    return ;}
	if (heredoc_handle(mshell) == EXIT_FAILURE)
		return ;
    if (check_is_builtin(&mshell->cmds[0]) && mshell->count_cmds == 1)
		execute_builtins(mshell, &mshell->cmds[0], &status);
    else
		handle_pipeline(mshell, 0, &status);
	mshell->exit_code = status;
	printf("status: %d\n", status);
}
