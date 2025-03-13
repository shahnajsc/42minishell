#include "minishell.h"

long long ft_atoll(const char *str, long long number, long long check)
{
    int signcount;

	signcount = 1;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            signcount = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        check = (number * 10) + (*str - '0');
        if (check / 10 != number && signcount == 1)
            return (LLONG_MAX);
        if (check / 10 != number && signcount == -1)
            return (LLONG_MIN);
        number = check;
        str++;
    }
    return (number * signcount);
}

int 	process_exit_code(char *arg, int *exit_status)
{
	long long 	exit_nbr;

	exit_nbr = ft_atoll(arg, 0, 0);
	if (exit_nbr == LLONG_MAX || exit_nbr == LLONG_MIN)
		return (1);
	else if (exit_nbr < 0)
		exit_nbr = (exit_nbr % 256 + 256) % 256;
	else if (exit_nbr > 255)
		exit_nbr = exit_nbr % 256;
	*exit_status = (int)exit_nbr;
	return (0);
}
void 	handle_exit(char **args, int *exit_status)
{
	if (!args[1])
		*exit_status = 0;
	else if (!*args[1])
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);	
		ft_putstr_fd(": numeric argument required\n", 2);
		*exit_status = 2;
	}
	else if (!is_invalid_digit(args[1]) && args[2])
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": too many arguments\n", 2);
		*exit_status = -1;
	}
	else if (is_invalid_digit(args[1]) || process_exit_code(args[1], exit_status))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		*exit_status = 2;
	}
}
int 	exit_mshell(t_mshell *mshell)
{
	int 	status;

	status = mshell->exit_code;
	cleanup_mshell(mshell);
	exit (status);
}
int  ft_exit(t_mshell *mshell, char **args)
{
	int	exit_status;

	ft_putendl_fd("exit", STDOUT_FILENO);
	handle_exit(args, &exit_status);
	mshell->exit_code = exit_status;
	if (exit_status != -1)
		exit_mshell(mshell);
	return (exit_status);
}
/*

args only nbr -> too many arguments 		>> 		exit_stat >> 1     		 NO Ex

args only char -> numeric argument required  >> 	exit_stat >> 2  		YES Ex

args starts nbr .> too many arguments        >>     exit_stat >> 1     		 NO Ex

args starts char -> numeric argument required  >> 	exit_stat >> 2  		YES Ex

*/
