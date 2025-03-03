#include "minishell.h"

int 	is_invalid_digit(char *arg)
{
	int 	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+') 
        i++;
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i++;
	}
	return (0);
}
void 	process_exit_code(char *arg, int *exit_status)
{
	int 	nbr;

	nbr = 0;
	nbr = ft_atoi(arg);
	if (nbr < 0)
		nbr = (nbr % 256 + 256) % 256;
	else if (nbr > 255)
		nbr = nbr % 256;
	*exit_status = nbr;
}
void 	handle_exit(char **args, int *exit_status)
{	
	if (!args[1])
		*exit_status = 0;
	else if (!is_invalid_digit(args[1]) && args[2])
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putendl_fd("too many arguments", STDERR_FILENO);
		*exit_status = 1;
	}
	else if (is_invalid_digit(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		*exit_status = 2;
	}
	else if (args[1])
		process_exit_code(args[1], exit_status);
}
int 	exit_mshell(t_mshell *mshell, int  *exit_status)
{
	free_env(mshell->env);
	exit (*exit_status);
}
int  ft_exit(t_mshell *mshell, char **args)
{
	int 	exit_status;

	exit_status = 0;
	ft_putendl_fd("exit", STDOUT_FILENO); 
	handle_exit(args, &exit_status);
	printf("%d\n", exit_status);
	if (exit_status != 1)
		exit_mshell(mshell, &exit_status);
	return (0);
}
/*

args only nbr -> too many arguments 		>> 		exit_stat >> 1     		 NO Ex

args only char -> numeric argument required  >> 	exit_stat >> 2  		YES Ex

args starts nbr .> too many arguments        >>     exit_stat >> 1     		 NO Ex

args starts char -> numeric argument required  >> 	exit_stat >> 2  		YES Ex

*/