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


void 	execute_process(t_mshell *mshell, t_cmd *cmd, char ***copy_env)
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
	exit (126);
}

void 	wait_processes(t_mshell *mshell)
{
	int i;

	i = 0;
	while (i < mshell->count_cmds)
	{
		wait(NULL);
		i++;
	}
}
int  execute_child_command(t_mshell *mshell, int i)
{
    char **copy_env;

	copy_env = NULL;
    if (check_is_builtin(&mshell->cmds[i]))
    {
		if (execute_builtins(mshell, &mshell->cmds[i]) != SUCSSES)
		{
			cleanup_mshell(mshell);
			exit(EXIT_FAILURE);
		}
		else
			cleanup_mshell(mshell);
    }
    else
    {
        convert_env(mshell->env, &copy_env);
        execute_process(mshell, &mshell->cmds[i], &copy_env);
    }
	exit(EXIT_SUCCESS);
}

void child_redirection(t_mshell *mshell, int i)
{
	close(mshell->pipe_fd[0]); 
    if (mshell->prev_read_fd != STDIN_FILENO)
    {
        redirect_fd(mshell->prev_read_fd, STDIN_FILENO);
        close(mshell->prev_read_fd);
    }
    if (i < mshell->count_cmds - 1)
    {
		  
		redirect_fd(mshell->pipe_fd[1], STDOUT_FILENO);
		close(mshell->pipe_fd[1]);
    }
	else
		close(mshell->pipe_fd[1]); 

}

void parent_redirecton(t_mshell *mshell)
{
	close(mshell->pipe_fd[1]);
    if (mshell->prev_read_fd != STDIN_FILENO)
		close(mshell->prev_read_fd);
    mshell->prev_read_fd = mshell->pipe_fd[0];
}

void 	close_fds(t_mshell *mshell)
{
	if (mshell->pipe_fd[0] != STDIN_FILENO)
		close(mshell->pipe_fd[0]);
	if (mshell->pipe_fd[1] != -1)
		close(mshell->pipe_fd[1]);
}
int		create_child_process(t_mshell *mshell, pid_t p_id)
{
	if (p_id == -1)
	{
		ft_putendl_fd("minishell: fork failed", STDERR_FILENO);
		close_fds(mshell);
       	return (-1);
	}
	return (0);
}
// int		execute_single_external(t_mshell *mshell)
// {
// 	pid_t p_id;

// 	p_id = fork();
// 	if (create_child_process(mshell, p_id) == -1)
// 		return (EXIT_FAILURE);
// 	if (p_id == 0)
// 		execute_child_command(mshell, 0);
// 	else
// 		wait_processes(mshell);
// 	return (EXIT_FAILURE);
// }

int 	setup_pipe(t_mshell *mshell)
{
	if (pipe(mshell->pipe_fd) == -1)
	{
		ft_putstr_fd("minishell: pipe faile\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}
int 	handle_pipeline(t_mshell *mshell)
{
    int 	i;
    pid_t 	p_id;

	i = 0;
    while (mshell->cmds && i < mshell->count_cmds)
    {
		if (setup_pipe(mshell) == -1)
			return (EXIT_FAILURE);
		p_id = fork();
        if (create_child_process(mshell, p_id) == -1)
			return (EXIT_FAILURE);
        if (p_id == 0)
		{
			child_redirection(mshell, i);
			execute_child_command(mshell, i);
		}
        else
            parent_redirecton(mshell);
        i++;
    }
    if (mshell->prev_read_fd != STDIN_FILENO)
        close(mshell->prev_read_fd);
    wait_processes(mshell);
    mshell->prev_read_fd = STDIN_FILENO;
	return (EXIT_SUCCESS);
}
void    handle_command_execution(t_mshell *mshell)
{
    int    i;
	
    if (!mshell->cmds || mshell->count_cmds == 0)
        return ;
    i = 0;
    if (check_is_builtin(&mshell->cmds[0]) && mshell->count_cmds == 1)
        execute_builtins(mshell, &mshell->cmds[0]);
	// else if (!check_is_builtin(&mshell->cmds[0]) && mshell->count_cmds == 1)
	// 	execute_single_external(mshell);
    else
		handle_pipeline(mshell);
}
