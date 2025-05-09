/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:22:29 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/06 16:43:21 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_mshell			t_mshell;
typedef enum e_redirect_type	t_redirect_type;
typedef struct s_redirect		t_redirect;
typedef struct s_cmd			t_cmd;
typedef struct s_token			t_token;

//...............EXECUTION................//
int			check_is_builtin(t_cmd *cmd);
void		execute_cmds(t_mshell *mshell);
void		parent_process(t_mshell *mshell);

//...............UTILS................//
void		parent_process(t_mshell *mshell);
int			wait_all(t_mshell *mshell, int i);
char		**convert_env(t_env *env, char ***copy_env);
char		*get_command_path(t_mshell *mshell, t_cmd *cmd);
void		child_process(t_mshell *mshell, int i, int *status);
void		update_env_underscore(t_mshell *mshell);
void		error_return_path(t_mshell *mshell, char *err_in, char *msg,
				int status);

//..... ERROR  && CLEANUP .....//
void		close_fds(t_mshell *mshell);
int			setup_pipe(t_mshell *mshell);
int			allocate_pid(t_mshell *mshell);
int			execution_error(t_mshell *mshell, t_cmd *cmd, int status);
int			create_child_process(t_mshell *mshell, pid_t p_id);
int			clean_and_exit(t_mshell *mshell, char *msg, int status);

#endif
