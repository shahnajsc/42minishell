#include "minishell.h"

void redirect_fd(int from_fd, int to_fd)
{
    if (from_fd == to_fd)
        return; 
    if (dup2(from_fd, to_fd) == -1)
    {
        perror("minishell: dup2");
        exit(1);
    }
    if (from_fd != STDIN_FILENO && from_fd != STDOUT_FILENO && from_fd != STDERR_FILENO)
        close(from_fd);
}

int	set_rd_fds(t_cmd *cmd, int new_in_fd, int new_out_fd)
{
	if (new_in_fd != -2)
	{
		if (cmd->rd_fd[0] != -1 && cmd->rd_fd[0] != -2)
			close (cmd->rd_fd[0]);
		cmd->rd_fd[0] = new_in_fd;
	}
	if (new_out_fd != -2)
	{
		if (cmd->rd_fd[1] != -1 && cmd->rd_fd[1] != -2)
			close (cmd->rd_fd[1]);
		cmd->rd_fd[1] = new_out_fd;
	}
	if (new_in_fd == -1 || new_out_fd == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	redirect_handle_cmd(t_mshell *mshell, t_cmd *cmd, int len)
{
	int	i;
	t_redirect	*rds;
	int	fd[2];

	i = 0;
	rds = cmd->redirects;
	while (cmd->redirects && i < len)
	{
		fd[0] = -2;
		fd[1] = -2;
		// check amigous redirect
		if (rds[i].rd_type == RD_HEREDOC)
			fd[0] = get_heredoc_fd(mshell, rds, i); //use HD open
		else if (rds[i].rd_type == RD_IN)
			fd[0] = get_file_fd(mshell, rds[i].file_deli, rds[i].rd_type);
		else if (rds[i].rd_type == RD_OUT)
			fd[1] = get_file_fd(mshell, rds[i].file_deli, rds[i].rd_type);
		else if (rds[i].rd_type ==  RD_APPEND)
			fd[1] = get_file_fd(mshell, rds[i].file_deli, rds[i].rd_type);
		if (set_rd_fds(cmd, fd[0], fd[1]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	if (cmd->rd_fd[0] != -1 && cmd->rd_fd[0] != -2) // fd[0] = -2 fd[1] = -2 from prev func
		redirect_fd(cmd->rd_fd[0], STDIN_FILENO);
	if (cmd->rd_fd[1] != -1 && cmd->rd_fd[1] != -2)
		redirect_fd(cmd->rd_fd[1], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
