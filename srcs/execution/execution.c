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
        len = ft_strlen(env[i].key) + ft_strlen(env[i].value) + 2;  // +2 for '=' and '\0'
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
	*copy_env[i] = NULL;
    return (*copy_env);
}

void 	execute_subprocess(t_mshell *mshell, char ***copy_env)
{
	char *cmd_path;

	cmd_path = get_command_path(mshell, mshell->cmds);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
		ft_putendl_fd(mshell->cmds->cmd_name, STDERR_FILENO);
		cleanup_mshell(mshell);
		ft_free_grid((void **)*copy_env);
		exit(127);
	}
	execve(cmd_path, mshell->cmds->splitted_cmd, *copy_env);
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
void	create_subprocesses(t_mshell *mshell)
{
	int		i;
	pid_t 	p_id;
	char 	**copy_env;

	i = 0;
	copy_env = NULL;
	if (!mshell->cmds || mshell->count_cmds == 0)
        return ;
	while (mshell->cmds && i < mshell->count_cmds)
	{
		p_id = fork();
		if (p_id == -1)
		{	
			perror("Error");
			// ft_free_grid((void **)copy_env);
			return ;
		}
		if (p_id == 0)
		{
			if (check_is_builtin(&mshell->cmds[i]))
			{	
				execute_builtins(mshell, &mshell->cmds[i]);
				exit(EXIT_SUCCESS);  
			}
			else
			{	
				convert_env(mshell->env, &copy_env);
				execute_subprocess(mshell, &copy_env);
				exit(EXIT_SUCCESS);
			}
		}
		i++;
	}
	wait_processes(mshell);
}
void    execute_cmds(t_mshell *mshell)
{
    int    i;
	
    if (!mshell->cmds || mshell->count_cmds == 0)
        return ;
    i = 0;
    // if (mshell->count_cmds > 1)
    //     if (init_pipe(mshell, mshell->count_cmds))
    //         return (NULL);
    if (check_is_builtin(&mshell->cmds[0]) && mshell->count_cmds == 1)
        execute_builtins(mshell, &mshell->cmds[0]);
    else
		create_subprocesses(mshell);
}
