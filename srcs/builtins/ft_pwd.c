#include "minishell.h"

int	ft_pwd(void)
{
	char *cwd = getcwd(NULL, 0);

	if (!cwd)
	{	
		perror("Error");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
