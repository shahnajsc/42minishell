#include "./minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	// if (argc != 1)
	// {
	// 	ft_putstr_fd("Error\n", 2);
	// 	ft_putstr_fd("Correct command format: ./minishell\n", 2);
	// 	exit(1);
	// }
	printf("\n");
	// printf("value of ARGV[0]: %s\n", argv[0]);
	printf("value of ENVP[0]: %s\n", envp[0]);
	printf("\n");
	return (0);
}
