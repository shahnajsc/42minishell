#include "minishell.h"

void	redirect_fd(int from_fd, int to_fd)
{
	if (dup2(from_fd, to_fd) == -1)
	{
		perror("minishell: dup2");
		close(from_fd);
		//exit(1);
	}
	close(from_fd);
}

int	redirect_handle_cmd(t_mshell *mshell, t_redirect *rd_list, int *fd)
{
	int	i;

	if (!rd_list)
		return (1);
	i = 0;
	while (rd_list && rd_list[i].rd_type)
	{
		// check amigous redirect
		if (rd_list[i].rd_type == RD_HEREDOC)
			fd[0] = get_heredoc_fd(mshell, rd_list[i].file_deli); //use HD open
		else if (rd_list[i].rd_type == RD_IN)
			fd[0] = get_file_fd(mshell, rd_list[i].file_deli, rd_list[i].rd_type);
		else if (rd_list[i].rd_type == RD_OUT)
			fd[1] = get_file_fd(mshell, rd_list[i].file_deli, rd_list[i].rd_type);
		else if (rd_list[i].rd_type ==  RD_APPEND)
			fd[1] = get_file_fd(mshell, rd_list[i].file_deli, rd_list[i].rd_type);
		i++;
	}
	if (fd[0] == -1 || fd[1] == -1)
		return (1);
	if (fd[0] != -1 && fd[0] != -2) // fd[0] = -2 fd[1] = -2 from prev func
		redirect_fd(fd[0], STDIN_FILENO);
	if (fd[1] != -1 && fd[1] != -2)
		redirect_fd(fd[1], STDOUT_FILENO);
	return (0);
}
