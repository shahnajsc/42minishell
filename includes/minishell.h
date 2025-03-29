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
# include "builtins.h"
# include "redirect.h"
# include "execution.h"
# include "../libft/includes/libft.h"


// Library
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "minishell>> "

typedef struct	s_mshell
{
	t_env			*env;
	int				count_cmds;
	t_cmd			*cmds;
	int				pipe_fd[2];
	int 			prev_read_fd;
	pid_t 			*p_id;
	int				exit_code;
}	t_mshell;


//FUNCTIONS

int		minishell(t_mshell *mshell);
void	cleanup_mshell(t_mshell *mshell);

#endif
