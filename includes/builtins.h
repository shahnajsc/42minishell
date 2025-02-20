#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env {

	char		*key;
	char		*value;

} t_env;

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
void	ft_echo(t_env **env, char *str);
void 	update_env(t_env **env, const char *key, const char *set_value);

#endif
