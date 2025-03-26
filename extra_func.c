
// static int	assign_pipe_fds(t_mshell *mshell, int **fds, int cmd_count, int i)
// {
// 	if (!mshell || !fds)
// 		return (1);
// 	if (pipe(fds[i]) == -1)
// 		return (1);
// 	if (i == 0)
// 		mshell->cmds[i].in_fd = STDIN_FILENO;
// 	else
// 		mshell->cmds[i].in_fd = fds[i - 1][0];
// 	if (i == (cmd_count - 1))
// 		mshell->cmds[i].out_fd = STDOUT_FILENO;
// 	else
// 		mshell->cmds[i].out_fd = fds[i][1];
// 	return (0);
// }

// static int	init_pipe(t_mshell *mshell, int cmd_count)
// {
// 	int	**fds;
// 	int	i;

// 	i = -1;
// 	fds = (int **)malloc((cmd_count) * sizeof(int *));
// 	if (!fds)
// 		return (1);
// 	while (fds && ++i < (cmd_count - 1))
// 	{
// 		fds[i] = (int *)malloc(2 * sizeof(int));
// 		if (!fds[i])
// 		{
// 			ft_free_grid((void **)fds);
// 			return (1);
// 		}
// 		if (assign_pipe_fds(mshell, fds, cmd_count, i))
// 			return (ft_free_grid((void **)fds), 1);
// 	}
// 	fds[i] = NULL;
// 	mshell->pipe_fds = fds;
// 	return (0);
// }
// void	reset_close_fds(t_cmd)
// {

// }


// void	builtins_in_parent(t_mshell *mshell, t_cmd *cmd)
// {
// 	cmd->i_o_fd[0] = dup(STDIN_FILENO);
// 	cmd->i_o_fd[1] = dup(STDOUT_FILENO);

// 	int len;

// 	len = get_rd_list_len(cmd->token);
// 	if (redirect_handle_cmd(mshell, cmd, len) == EXIT_FAILURE)
// 	{
// 		redirect_fd(cmd->i_o_fd[0], STDIN_FILENO);
// 		redirect_fd(cmd->i_o_fd[1], STDOUT_FILENO);
// 		return ;
// 	}
// 	if (execute_builtins(mshell, cmd) > 0 )
// 	{
// 		redirect_fd(cmd->i_o_fd[0], STDIN_FILENO);
// 		redirect_fd(cmd->i_o_fd[1], STDOUT_FILENO);
// 		return;
// 	}
// 	redirect_fd(cmd->i_o_fd[0], STDIN_FILENO);
// 	redirect_fd(cmd->i_o_fd[1], STDOUT_FILENO);
// }

// void	external_in_parent(t_mshell *mshell, t_cmd *cmd, char ***copy_env)
// {
// 	int len;
// 	char *cmd_path;

// 	cmd->i_o_fd[0] = dup(STDIN_FILENO);
// 	cmd->i_o_fd[1] = dup(STDOUT_FILENO);
// 	len = get_rd_list_len(cmd->token);
// 	if (redirect_handle_cmd(mshell, cmd, len) == EXIT_FAILURE)
// 	{
// 		redirect_fd(cmd->i_o_fd[0], STDIN_FILENO);
// 		redirect_fd(cmd->i_o_fd[1], STDOUT_FILENO);
// 		return ;
// 	}
// 	cmd_path = get_command_path(mshell, cmd);
// 	  if (!cmd_path)
//     {
//         ft_putstr_fd(mshell->cmds->cmd_name, STDERR_FILENO);
//         ft_putstr_fd(": command not found\n", STDERR_FILENO);
//         ft_free_grid((void **)*copy_env);
//         cleanup_mshell(mshell);
//         exit(127);
//     }
//     execve(cmd_path, mshell->cmds->splitted_cmd, *copy_env);
//     perror("minishell");
//     ft_free_grid((void **)*copy_env);
//     cleanup_mshell(mshell);
//     free(cmd_path);
// 	redirect_fd(cmd->i_o_fd[0], STDIN_FILENO);
// 	redirect_fd(cmd->i_o_fd[1], STDOUT_FILENO);
//     exit (126);
// }
