#include "minishell.h"


static void convert_status (long long exit_nbr, int *exit_status)
{
	if (exit_nbr < 0)
		exit_nbr = (exit_nbr % 256 + 256) % 256;
	else if (exit_nbr > 255)
		exit_nbr = exit_nbr % 256;
	*exit_status = (int)exit_nbr;
}
static int	process_exit_code(char *arg, int *exit_status)
{
	long long	exit_nbr;
	const char	*ptr;

	ptr = arg;
	if (*ptr == '-' || *ptr == '+')
		ptr++;
	if (strcmp(ptr, "9223372036854775807") == 0)
	{
		if (*arg == '-')
			exit_nbr = -LLONG_MAX;
		else
			exit_nbr = LLONG_MAX;
	}
	else if (strcmp(ptr, "9223372036854775808") == 0 && *arg == '-')
		exit_nbr = LLONG_MIN;
	else
	{
		exit_nbr = ft_atoll(arg, 0, 0);
		if ((exit_nbr == LLONG_MAX && strcmp(arg, "9223372036854775807") != 0)
			|| (exit_nbr == LLONG_MIN && strcmp(arg,
					"-9223372036854775808") != 0))
			return (EXIT_FAILURE);
	}
	convert_status(exit_nbr, exit_status);
	return (EXIT_SUCCESS);
}

static void	handle_exit(char **args, int *exit_status)
{
	if (!args[1])
		*exit_status = 0;
	else if (!is_invalid_digit(args[1]) && args[2])
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd("too many arguments\n", 2);
		*exit_status = -1;
	}
	else if (!*args[1] || is_invalid_digit(args[1])
		|| process_exit_code(args[1], exit_status))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		*exit_status = 2;
	}
}

int	exit_mshell(t_mshell *mshell, int *status)
{
	if (mshell->cmds && mshell->count_cmds == 1)
		ft_putendl_fd("exit", STDOUT_FILENO);
	cleanup_mshell(mshell);
	exit(*status);
}

int	ft_exit(t_mshell *mshell, char **args)
{
	int	exit_status;

	if (!mshell || !mshell->env || !args)
		return (0);
	handle_exit(args, &exit_status);
	if (exit_status != -1)
		exit_mshell(mshell, &exit_status);
	else
		exit_status = 1;
	return (exit_status);
}
