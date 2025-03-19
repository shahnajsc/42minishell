#include "minishell.h"

int	get_heredoc_fd(t_mshell *mshell, t_redirect *rd_list, int i)
{
	int	pipe_fd[2];
	char *hd_lines;

	hd_lines = ft_strdup("");
	if (!hd_lines)
		return (1);
	if (pipe(pipe_fd) == -1)
	{
		free(hd_lines);
		return(file_error(mshell, NULL, "Pipe open failed", 111));
	}
	heredoc_handle(mshell, rd_list, i, &hd_lines);
	free(hd_lines);
	close (pipe_fd[1]);
	return (pipe_fd[0]);
}

int	get_file_fd(t_mshell *mshell, char *path, t_redirect_type rd_type)
{
	int	file_fd;

	file_fd = 0;
	// if (check_is_dir(path) == -1)
	// 	return(file_error(mshell, path, "Is a directory", 111));
	printf("func filenam: %s\n", path);
	if (rd_type == RD_IN)
	{
		printf(" in filenam: %s\n", path);
		printf("infile1 fd: %d\n", file_fd);
		if (access(path, F_OK) == 0)
			return(file_error(mshell, path, "No such file or directory", 111));
		else if (access(path, R_OK) == -1)
			return(file_error(mshell, path, "Permission denied", 111));
		printf("infile2 fd: %d\n", file_fd);
		file_fd = open(path, O_RDONLY, 0444);
		printf("infile3 fd: %d\n", file_fd);
	}
	else
	{
		printf("out filenam: %s\n", path);
		if (access(path, F_OK) == 0 && access(path, W_OK) == -1)
			return(file_error(mshell, path, "Permission denied", 111));
		if (rd_type == RD_APPEND)
			file_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (rd_type == RD_OUT)
			file_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (file_fd == -1)
		return(file_error(mshell, path, "No such file or directory", 111));
	return (file_fd);
}

