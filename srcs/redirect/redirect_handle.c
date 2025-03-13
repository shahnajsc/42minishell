#include "minishell.h"

int	redirect_handle_cmd(t_mshell *mshell, t_redirect *rd_list, int *fd)
{
	int	i;

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
}
