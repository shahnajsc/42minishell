#include "minishell.h"
char	*heredoc_join(char *hd_lines, char *line)
{
	char *new_hd;
	char *temp;

	if (!hd_lines)
		return (NULL);
	temp = ft_strjoin(hd_lines, line);
	free(hd_lines);
	free(line);
	if (!temp)
		return (NULL);
	new_hd = ft_strjoin(temp, "\n");
	free(temp);
	if (!new_hd)
		return (NULL);
	return (new_hd);
}

void	heredoc_handle(t_mshell *mshell, char *deli, int hd_fd, char *hd_lines)
{
	char *line;

	if (!hd_lines)
		return ;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			//print error and check if it is interupted by SIG
			break ; // or exit??
		}
		if (ft_strncmp(line, deli, ft_strlen(deli)) == 0) // && line[ft_strlen(deli) + 1] == '\n'
		{
			free(line);
			break ;
		}
		hd_lines = heredoc_join(hd_lines, line);
		if (!hd_lines)
			return ;
	}
	free(deli);
	deli = hd_lines;
}
