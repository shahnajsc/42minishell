#include "minishell.h"

int	is_newline(char *c, int *nl)
{
	if (ft_strcmp(c, "-n") == 0)
	{
		*nl= 0;
		return (1);
	}
	*nl = 1;
	return (0);
}
int	ft_echo(t_mshell *mshell, char **args)
{
	int 		i;
	int 		new_line;

	i = 1;
	new_line = 1;
	if (args[i] && is_newline(args[i], &new_line))
		i++;
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	mshell->exit_code = 0;
	return (0);
}
