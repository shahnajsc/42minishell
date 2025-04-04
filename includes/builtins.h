/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:46:22 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/04 11:57:41 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdlib.h>

typedef struct s_mshell			t_mshell;
typedef enum e_redirect_type	t_redirect_type;
typedef struct s_redirect		t_redirect;
typedef struct s_cmd			t_cmd;
typedef struct s_token			t_token;

typedef struct s_env
{
	char	*key;
	char	*value;

}	t_env;

typedef enum s_cd_error
{
	SUCSSES,
	FAILURE,
	NO_FILE,
	NOT_DIR,
	NO_PERM,
	HOME_UNSET,
	MANY_ARGS,
	GETCWD,
}	t_cd_error;

//........BUILTINS..........//
int			ft_pwd(t_mshell *mshell);
int			ft_cd(t_mshell *mshell, char **args);
int			ft_env(t_mshell *mshell, char **args);
int			ft_exit(t_mshell *mshell, char **args);
int			ft_echo(t_mshell *mshell, char **args);
int			ft_export(t_mshell *mshell, char **args);
int			ft_unset(t_mshell *mshell, char **keys, int i, int index);
int			execute_builtins(t_mshell *mshell, t_cmd *cmd, int *status);

//........UTILS..........//
int			env_size(t_env *env);
void		sort_env(t_env *env);
t_env		*init_env(char **envp);
char		*ft_strndup(char *src, size_t n);
t_env		*get_env_var(t_env *env, char *key);
int			export_copy(t_env *dest, t_env *src);
void		process_without_sign(t_env **env, char *arg);
int			compare_keys(const char *a, const char *b);
void		add_env_var(t_env **old_env, char *key, char *value);
void		process_with_sign(t_env **env, char *arg, char *sign);
int			update_env_state(t_mshell *mshell, char *current_pwd);
void		update_cd(t_env **env, const char *key, const char *set_path);
long long	ft_atoll(const char *str, long long number, long long check);

//........VALIDATION.........//
int			is_invalid_digit(char *arg);
int			is_invalid_identifier(char *identifier);

//..... ERROR  && CLEANUP .....//
void		free_env(t_env *env);
int			exit_mshell(t_mshell *mshell, int *status);
int			cd_error(char **args, t_cd_error err);
void		mshell_lvl_error(t_env **env, char *new_lvl, t_env *shlvl);
int			builtins_error(char *arg, char *err_msg, char *free_str);

#endif
