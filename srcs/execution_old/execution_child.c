// #include  "minishell.h"

// void	builtins_in_child(t_mshell *mshell, t_cmd *cmd)
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
// 		return ;
// 	}
// 	redirect_fd(cmd->i_o_fd[0], STDIN_FILENO);
// 	redirect_fd(cmd->i_o_fd[1], STDOUT_FILENO);
// 	cleanup_mshell(mshell);
// 	exit(EXIT_SUCCESS);
// }

// void 	execute_subprocess(t_mshell *mshell, t_cmd *cmd, char ***copy_env)
// {
// 	char *cmd_path;
// 	int len;

// 	// cmd->i_o_fd[0] = dup(STDIN_FILENO);
// 	// cmd->i_o_fd[1] = dup(STDOUT_FILENO);
// 	len = get_rd_list_len(cmd->token);
// 	if (redirect_handle_cmd(mshell, cmd, len) == EXIT_FAILURE)
// 	{
// 		redirect_fd(cmd->i_o_fd[0], STDIN_FILENO);
// 		redirect_fd(cmd->i_o_fd[1], STDOUT_FILENO);
// 		return ;
// 	}
// 	cmd_path = get_command_path(mshell, cmd);
// 	if (!cmd_path)
// 	{
// 		ft_putstr_fd(cmd->cmd_name, STDERR_FILENO);
// 		ft_putstr_fd(": command not found\n", STDERR_FILENO);
// 		ft_free_grid((void **)*copy_env);
// 		cleanup_mshell(mshell);
// 		exit(127);
// 	}
// 	execve(cmd_path, cmd->splitted_cmd, *copy_env);
// 	perror("minishell");
// 	ft_free_grid((void **)(*copy_env));
// 	// redirect_fd(cmd->i_o_fd[0], STDIN_FILENO);
// 	// redirect_fd(cmd->i_o_fd[1], STDOUT_FILENO);
// 	cleanup_mshell(mshell);
// 	free(cmd_path);
// 	exit (126);
// }

// void 	children(t_mshell *mshell, int i)
// {
// 	char 	**copy_env;

// 	copy_env = NULL;

// 	if (check_is_builtin(&mshell->cmds[i]))
// 	{
// 		builtins_in_child(mshell, &mshell->cmds[i]);
// 		//execute_builtins(mshell, &mshell->cmds[i]);
// 		//builtins_in_parent(mshell, &mshell->cmds[i]);
// 		cleanup_mshell(mshell);
// 		exit(EXIT_SUCCESS);
// 	}
// 	else
// 	{
// 		copy_env = convert_env(mshell->env, &copy_env);
// 		if (!copy_env)
// 			return ;
// 		execute_subprocess(mshell, &mshell->cmds[i], &copy_env);
// 	//	ft_free_grid((void **)(*copy_env));
// 		//exit(EXIT_SUCCESS);
// 	}
// }

// void call_child_process(t_mshell *mshell, int *pipe_fd, int i)
// {
// 	if (mshell->prev_read_fd != STDIN_FILENO)
// 	{
// 		redirect_fd(mshell->prev_read_fd, STDIN_FILENO);
// 	}
// 	if (i < mshell->count_cmds - 1)
// 	{
// 		close(pipe_fd[0]);
// 		redirect_fd(pipe_fd[1], STDOUT_FILENO);
// 	}
// 	else
// 	{
// 		close(pipe_fd[0]);
// 		close(pipe_fd[1]);
// 	}
// 	children(mshell, i);
// }

// void call_parent_process(t_mshell *mshell, int *pipe_fd, int i)
// {
// 	(void)i;

// 	close(pipe_fd[1]);
//     if (mshell->prev_read_fd != STDIN_FILENO)
// 		close(mshell->prev_read_fd);
//     mshell->prev_read_fd = pipe_fd[0];
// }

// // void	external_in_parent(t_mshell *mshell, t_cmd *cmd, char ***copy_env)
// // {
// // 	int len;
// // 	char *cmd_path;

// // 	cmd->i_o_fd[0] = dup(STDIN_FILENO);
// // 	cmd->i_o_fd[1] = dup(STDOUT_FILENO);
// // 	len = get_rd_list_len(cmd->token);
// // 	if (redirect_handle_cmd(mshell, cmd, len) == EXIT_FAILURE)
// // 	{
// // 		redirect_fd(cmd->i_o_fd[0], STDIN_FILENO);
// // 		redirect_fd(cmd->i_o_fd[1], STDOUT_FILENO);
// // 		return ;
// // 	}
// // 	cmd_path = get_command_path(mshell, cmd);
// // 	  if (!cmd_path)
// //     {
// //         ft_putstr_fd(mshell->cmds->cmd_name, STDERR_FILENO);
// //         ft_putstr_fd(": command not found\n", STDERR_FILENO);
// //         ft_free_grid((void **)*copy_env);
// //         cleanup_mshell(mshell);
// //         exit(127);
// //     }
// //     execve(cmd_path, mshell->cmds->splitted_cmd, *copy_env);
// //     perror("minishell");
// //     ft_free_grid((void **)*copy_env);
// //     cleanup_mshell(mshell);
// //     free(cmd_path);
// // 	redirect_fd(cmd->i_o_fd[0], STDIN_FILENO);
// // 	redirect_fd(cmd->i_o_fd[1], STDOUT_FILENO);
// //     exit (126);
// // }
