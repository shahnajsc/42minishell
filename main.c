#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    printf("Readline headers are found!\n");
    return 0;
}

// int	ft_strcmp(char *s1, char *s2)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while (s1[i] == s2[i] && s1[i] != '\0')
// 		i++;
// 	return (s1[i] - s2[i]);
// }

// int main(int argc, char **argv)
// {
// 	if (argc != 3)
// 		printf("error\n");
// 	else
// 	{
// 		int i = ft_strcmp(argv[1], argv[2]);
// 		printf("ag1:[%s]\n", argv[1]);
// 		printf("ag1:[%s]\n", argv[2]);
// 		printf("ret value:[%d]\n", i);
// 	}
// }


//#include "minishell.h"

// static int mshell_data_init(t_mshell *mshell, char **envp)
// {
// 	ft_memset(mshell, 0, sizeof(mshell));
// 	mshell->envp = envp_duplicate(envp);
// 	if (!mshell->envp)
// 		return (1); // error msg
// 	mshell->count_cmds = 0;
// 	mshell->cmds = NULL;
// 	mshell->exit_code = 0;
// 	return (0);
// }



// int	main(int argc, char **argv, char **envp)
// {
// 	t_mshell mshell;

// 	if (argc != 1)
// 	{
// 		ft_putstr_fd("Error: Correct  argument: ./minishell\n", 2);
// 		exit(EXIT_FAILURE);
// 	}
// 	(void)argv;
// 	if (mshell_data_init(&mshell, envp))
// 		exit(EXIT_FAILURE);
// 	minishell(&mshell);
// }
