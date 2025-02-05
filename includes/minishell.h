#ifndef MINISHELL_H
# define MINISHELL_H

//required library
// fcntl: file handle
// sys/wait: process wait(waitpid)
// stdio: perror
// errno: strerrno

// header files
# include "pipe.h"
# include "envp.h"
# include "parse.h"
# include "../libft/includes/libft.h"


// Library
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
//# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "minishell>>"

typedef struct	s_mshell
{
	char			**envp;
	char			*input;
	t_token_list	*token_list;
}	t_mshell;

//FUNCTIONS
void	minishell(t_mshell *mshell);

#endif
