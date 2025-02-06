#include "minishell.h"
void	ft_pwd(void)
{
	char *cwd = getcwd(NULL, 0);

	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	else
		perror("Error");
}
