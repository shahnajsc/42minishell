#include "minishell.h"

int	get_heredoc_fd(t_mshell *mshell, char *path)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	write(pipe_fd[1], "> ", 2);
	close (pipe_fd[1]);
	return (pipe_fd[0]);
}

int	get_file_fd(t_mshell *mshell, char *path, t_redirect_type rd_type)
{
	int	file_fd;

	file_fd = 0;
	if (check_is_dir(path) == -1)
		printf("Is a directory\n"); // make error mechanism
	if (rd_type == RD_IN)
	{
		if (access(path, F_OK) == 0)
			printf("No such file or directory\n");
		else if (access(path, R_OK) == -1)
			printf("Permission denied\n");
		file_fd = open(path, O_RDONLY, 0444);
	}
	else
	{
		if (access(path, F_OK) == 0 && access(path, W_OK) == -1)
			printf("Permission denied\n");
		if (rd_type == RD_APPEND)
			file_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (rd_type == RD_OUT)
			file_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (file_fd == -1)
		printf("No such file or directory\n");
	return (file_fd);
}

