#include "minishell.h"

void	minishell(t_mshell *mshell)
{
	char	*input_str;

	int fd;
	char *line;

	fd  = open("outfile", O_RDONLY, 0444);
	if (fd == -1)
		printf("error opening file\n");
	line = read_line(fd);
	while (line)
	{
		printf("line: %s", line);
		free(line);
		line = read_line(fd);
		if (!line)
			break ;
	}
	free(line);
	close(fd);
	setup_signal_handlers();
	while (1) // need signal handle for exit
	{
		input_str = readline(PROMPT);
		if (!input_str)
			exit_mshell(mshell);
		else
		{
			add_history(input_str);
			if (parse_input(mshell, input_str))
			{
				free(input_str);
				continue ;
			}
			free(input_str);
			if (mshell->cmds)
				execute_cmds(mshell);
			// printf("%d\n", status);
			cleanup_on_loop(mshell);
		}
	}
	rl_clear_history();
}
