#include "minishell.h"

static int	is_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
static int	is_newline(char *str, int *nl)
{
	if (!str || !nl || !*nl)
		return (0);
	if ((str[0] == '-' && is_n(str)))
	{
		*nl = 0;
		return (1);
	}
	*nl = 1;
	return (0);
}
int	ft_echo(t_mshell *mshell, char **args)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (!mshell || !mshell->env || !args)
		return (0);
	if (args[i] && is_newline(args[i], &new_line))
	{
		i++;
		while (args[i] && args[i][0] == '-' && is_n(args[i]))
			i++;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	// printf("echo exit: %d\n", mshell->exit_code);
	//printf("echo arg: %s\n", args[1]);
	return (0);
}
