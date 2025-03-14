#include "minishell.h"

int	get_heredoc_fd(t_mshell *mshell, char *path)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		file_error(mshell, path, "Pipe open failed", 111);
	write(pipe_fd[1], "> ", 2);
	close (pipe_fd[1]);
	return (pipe_fd[0]);
}

int	get_file_fd(t_mshell *mshell, char *path, t_redirect_type rd_type)
{
	int	file_fd;

	file_fd = 0;
	// if (check_is_dir(path) == -1)
	// 	file_error(mshell, path, "Is a directory", 111);
	if (rd_type == RD_IN)
	{
		if (access(path, F_OK) == 0)
			file_error(mshell, path, "No such file or directory", 111);
		else if (access(path, R_OK) == -1)
			file_error(mshell, path, "Permission denied", 111);
		file_fd = open(path, O_RDONLY, 0444);
	}
	else
	{
		if (access(path, F_OK) == 0 && access(path, W_OK) == -1)
			file_error(mshell, path, "Permission denied", 111);
		if (rd_type == RD_APPEND)
			file_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (rd_type == RD_OUT)
			file_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (file_fd == -1)
		file_error(mshell, path, "No such file or directory", 111);
	return (file_fd);
}

