#include "minishell.h"

int	ft_pwd(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("minishell: pwd:", 2);
		if (errno == ENOENT)
       		ft_putendl_fd("Current directory no longer exists", 2);
		else if (errno == EACCES)
	        ft_putendl_fd("Permission denied", 2);
	    else if (errno == ELOOP) 
	        ft_putendl_fd("Too many symbolic links", 2);
	    else if (errno == ENAMETOOLONG) 
	        ft_putendl_fd("File name too long", 2);
	    else 
	        ft_putendl_fd("Error: getcwd failed", 2);
		free(cwd);
		return (1);
	}
	else
		ft_putendl_fd(cwd, STDOUT_FILENO);
    free(cwd);
	return (0);
}
