/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:46:41 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/04 11:58:47 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_mshell	t_mshell;

typedef enum e_token_type
{
	EMPTY,
	CMD,
	REDIRECT,
	FILENAME,
	DELIMETER,
}	t_token_type;

typedef enum e_redirect_type
{
	RD_IN,
	RD_HEREDOC,
	RD_OUT,
	RD_APPEND,
	NONE,
}	t_redirect_type;

typedef struct s_token
{
	t_token_type	tok_type;
	char			*tok_value;
	struct s_token	*next;
}	t_token;

typedef struct s_redirect
{
	t_redirect_type	rd_type;
	char			*file_deli;
	char			*hd_lines;
}					t_redirect;

typedef struct s_cmd
{
	t_token		*token;
	t_redirect	*redirects;
	int			is_hd_quote;
	char		*cmd_str;
	char		*cmd_name;
	char		**splitted_cmd;
	int			std_fd[2];
	int			redi_fd[2];
}	t_cmd;

typedef enum e_mshell_err
{
	ERR_SYN,
	ERR_BUILTIN,
	ERR_EXEV,
}	t_mshell_err;

typedef enum e_syntax_err
{
	ERR_P,
	ERR_Q,
	ERR_BACK_S,
	ERR_WHITE_S,
	ERR_RD,
	ERR_COMN,
}	t_syntax_err;

//.......VALIDATION.....//////
int				check_char_whitespaces(char c);
int				check_str_whitespaces(char *input_str);
char			*skip_quoted_part(char *input_str);
char			*skip_unquoted_part(char *input_str);
int				pre_validation_input(t_mshell *mshell, char *input_str);

//...... PARSE .....////
int				parse_input(t_mshell *mshell, char *input_str);
char			**splitted_cmd(t_mshell *mshell, int i);

//...... TOKEN .....///
int				tokenize_input(t_mshell *mshell, char *input_str);
char			*get_redir_token_value(char *cmd_str, int *i);
void			add_new_token(t_token **head_token, t_token *new_token);
t_token			*create_tokens_list(t_mshell *mshell, char *cmd_str,
					int cmd_id);
t_token			*post_process_token(t_mshell *mshell, t_token *head_token,
					int cmd_id);
t_token			*expand_token_values(t_mshell *mshell, t_token *head_token);
t_token			*remove_token_quotes(t_mshell *mshell,
					t_token *head_token, int cmd_id);
t_token			*merge_consequtive_token(t_token *head_token);
char			*expand_text_token(t_mshell *mshell, char *tok_val, int i);
char			*replace_var(char *token, int *i);
t_token			*delete_empty_token(t_token *head_token);

//........REDIRECT..........//
int				get_rd_list_len(t_token *token);
t_redirect		*create_redirects_list(t_mshell *mshell, int cmd_id);

//..... ERROR  && CLEANUP .....//
int				syntax_pre_error(t_mshell *mshell, t_syntax_err syn_err,
					char *err_value);
void			cleanup_on_loop(t_mshell *mshell);
// int		parse_error(char *err_msg, int err_ret);

//......UTILS......////
int				check_char_is_quote(char c);
int				count_pipes(char *input_str);
char			**split_input_by_pipes(int cmd_count, char *input_str);
t_token_type	get_token_type(char *cmd_str, int i);
int				check_char_is_redirect(char c);
char			*get_token_envkey(char *token_value, int i);
char			*get_env_key_value(t_mshell *mshell, char *env_key);
void			clean_free_str(char *cmd_str);

//......TEST FUNCTIONS.......///
void			print_token_list(t_token *token_list);
void			print_splitted_cmds(char **cmds);
void			print_command_list(t_mshell *mshell);

void  print_command_list(t_mshell *mshell);

#endif
