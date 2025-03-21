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


void 	execute_subprocess(t_mshell *mshell, t_cmd *cmd, char ***copy_env)
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
void 	children(t_mshell *mshell, int i)
{
	char 	**copy_env;
	copy_env = NULL;
	// printf("execution\n");
	if (check_is_builtin(&mshell->cmds[i]))
	{	
		execute_builtins(mshell, &mshell->cmds[i]);
		cleanup_mshell(mshell);
		exit(EXIT_SUCCESS);  
	}
	else
	{	
		convert_env(mshell->env, &copy_env);
		execute_subprocess(mshell, &mshell->cmds[i], &copy_env);
		exit(EXIT_SUCCESS);
	}
}

void call_child_process(t_mshell *mshell, int *pipe_fd, int i)
{
	//printf("child main[%d]\n", i);
	if (mshell->prev_read_fd != STDIN_FILENO)
	{
		redirect_fd(mshell->prev_read_fd, STDIN_FILENO);
	}
	if (i < mshell->count_cmds - 1)
	{
		// printf("child + i[%d]\n", i + 1);
		close(pipe_fd[0]);
		redirect_fd(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	// printf("works [%d]\n", i);
	children(mshell, i);
	
}

void call_parent_process(t_mshell *mshell, int *pipe_fd, int i)
{
	if (mshell->prev_read_fd != STDIN_FILENO)
	{
		close(mshell->prev_read_fd);
	}
	if (i < mshell->count_cmds - 1)
	{
		close(pipe_fd[1]);
		mshell->prev_read_fd = pipe_fd[0];
	}

}

void	create_subprocesses(t_mshell *mshell)
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
			return ;
		}
		p_id = fork();
		if (p_id == -1)
		{	
			perror("Error");
			return ;
		}
		if (p_id == 0)
		{
			call_child_process(mshell, pipe_fd, i);
		}
		else
			call_parent_process(mshell, pipe_fd, i);
		i++;
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait_processes(mshell);
}
void    execute_cmds(t_mshell *mshell)
{
    int    i;
	
    if (!mshell->cmds || mshell->count_cmds == 0)
        return ;
    i = 0;
    if (check_is_builtin(&mshell->cmds[0]) && mshell->count_cmds == 1)
        execute_builtins(mshell, &mshell->cmds[0]);
    else
		create_subprocesses(mshell);
}
