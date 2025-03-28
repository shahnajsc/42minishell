#include "minishell.h"

int	check_is_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd_name, "env") == 0
		|| ft_strcmp(cmd->cmd_name,"pwd") == 0
		|| ft_strcmp(cmd->cmd_name, "export") == 0
		|| ft_strcmp(cmd->cmd_name, "cd") == 0
		|| ft_strcmp(cmd->cmd_name, "echo") == 0
		|| ft_strcmp(cmd->cmd_name, "exit") == 0
		|| ft_strcmp(cmd->cmd_name, "unset") == 0)
		return (1);
	return (0);
}

char **convert_env(t_env *env, char ***copy_env)
{
    int i;
    int len;

    *copy_env = ft_calloc(env_size(env) + 1, sizeof(char *));
    if (!(*copy_env))
        return (NULL);
    i = 0;
    while (env[i].key != NULL)
    {
        len = ft_strlen(env[i].key) + ft_strlen(env[i].value) + 2;
        (*copy_env)[i] = ft_calloc(len, sizeof(char));
        if (!(*copy_env)[i])
        {
            ft_free_grid((void **)(*copy_env));
            return (NULL);
        }
        ft_strlcpy((*copy_env)[i], env[i].key, ft_strlen(env[i].key) + 1);
        ft_strlcat((*copy_env)[i], "=", len);
        ft_strlcat((*copy_env)[i], env[i].value, len);
        i++;
    }
    (*copy_env)[i] = NULL;
    return (*copy_env);
}

void child_redirection(t_mshell *mshell, int i, int *status)
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

void parent_redirecton(t_mshell *mshell)
{
	close(mshell->pipe_fd[1]);
    if (mshell->prev_read_fd != STDIN_FILENO)
		close(mshell->prev_read_fd);
    mshell->prev_read_fd = mshell->pipe_fd[0];
}
int     ft_wait(t_mshell *mshell, pid_t pid, int *wstatus)
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
int	wait_process(t_mshell *mshell, pid_t p_id)
{
    int wstatus;
    int  exit_status;

    exit_status = EXIT_SUCCESS;
	if (ft_wait(mshell, p_id, &wstatus) == -1)
        exit_status = EXIT_FAILURE;
    setup_signal_handlers();
	if (WIFEXITED(wstatus))
	    exit_status = WEXITSTATUS(wstatus);
    else if (WIFSIGNALED(wstatus))
    {
        exit_status = 128 + WTERMSIG(wstatus);
        if (WTERMSIG(wstatus) == SIGQUIT)
            ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
    }
    else
    {    exit_status = EXIT_FAILURE;}
	return (exit_status);
}
