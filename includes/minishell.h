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
# include "../libft/includes/libft.h"


// Library
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
#include <sys/stat.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "minishell>>"

typedef struct	s_mshell
{
	char	**envp;
	char	*input;
}	t_mshell;

typedef enum {
	CMD = 1,
	ARG,
	PIPE,
	REDIRECT_OUT,
	REDIRECT_IN,
	APPEND_OUT,
	HERE_DOC
}  token_type;

typedef struct s_env {

	char		*key;
	char		*value;

} t_env;




//FUNCTIONS
// void	minishell(t_mshell *mshell);
int 	env_size(char **env);
void	ft_env(t_env *env);
int		ft_pwd(void);
int 	ft_cd(t_env **env, char *path);
char 	*ft_strndup(char *src, size_t n);
void 	export_var(t_env **env, char *str);
t_env	*duplicate_env(char **envp, t_env **env);
void 	 free_env(t_env *env, int size);
void 	ft_export(t_env *env);
void 	export_var(t_env **env, char *str);
void 	update_env(t_env **env, const char *key, const char *set_value);

#endif
