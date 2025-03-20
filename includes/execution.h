#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_mshell t_mshell;
typedef enum e_redirect_type t_redirect_type;
typedef struct s_redirect t_redirect;

//...............FUNCTIONS................//
void	execute_cmds(t_mshell *mshell);
char	*get_command_path(t_mshell *mshell, t_cmd *cmd);
void	builtins_in_parent(t_mshell *mshell, t_cmd *cmd);

#endif
