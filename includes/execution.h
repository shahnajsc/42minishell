#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_mshell t_mshell;
typedef enum e_redirect_type t_redirect_type;
typedef struct s_redirect t_redirect;

//...............FUNCTIONS................//
void	execute_cmds(t_mshell *mshell);
char	*get_command_path(t_mshell *mshell, t_cmd *cmd);
void	call_parent_process(t_mshell *mshell, int *pipe_fd, int i);
void	call_child_process(t_mshell *mshell, int *pipe_fd, int i);
int	builtins_in_parent(t_mshell *mshell, t_cmd *cmd);

//...........UTILS.........//
int		check_is_builtin(t_cmd *cmd);
char	**convert_env(t_env *env, char ***copy_env);
int 	wait_processes(pid_t pid);

#endif
