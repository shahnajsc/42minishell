#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_mshell t_mshell;

typedef enum e_token_type{
	CMD,
	//ARG,
	//PIPE,
	RD_IN, //value :file name
	RD_HEREDOC, // value: Delimeter
	RD_OUT, // value file name
	RD_APPEND, // value filename
}  t_token_type;

typedef struct s_token
{
	t_token_type tok_type;
	char	*tok_value;
	struct s_token *next;
}	t_token;

typedef struct s_cmd
{
	t_token	*token;
	char	*cmd_str;
	char	**splitted_cmd;
	char	*cmd_name;
	int		in_fd;
	int		out_fd;
}	t_cmd;

// typedef struct	s_mshell
// {
// 	char			**envp;
// 	//char			*input;
// 	int				count_cmds;
// 	t_cmd			*cmds;
// 	int				exit_code;
// }	t_mshell;

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
	ERR_COMN, // Need  it???
}	t_syntax_err;
// FUNCTION.......

//.......VALIDATION.....//////
int		check_char_whitespaces(char c);
int		check_str_whitespaces(char *input_str);
char	*skip_quoted_part(char *input_str);
char	*skip_unquoted_part(char *input_str);
int		input_pre_validation(t_mshell *mshell, char *input_str);

//...... PARSE .....////
int		parse_input(t_mshell *mshell, char *input_str);

//...... TOKEN .....///
int		tokenize_input(t_mshell *mshell, char *input_str);
//t_token	*create_tokens_list(t_mshell *mshell, int index);
t_token *create_cmd_token(char *cmd_str, int *i, t_token_type t_type);
t_token	*create_other_token(int *i, t_token_type t_type);
void	add_new_token(t_token **head_token, t_token *new_token);

//..... ERROR .....//
int		syntax_pre_error(t_mshell *mshell, t_syntax_err syn_err, char *err_value);
//int		parse_error(char *err_msg, int err_ret);

//......UTILS......////
int		check_char_is_quote(char  c);
int		count_pipes(char *input_str);
char	**split_input_by_pipes(int cmd_count, char *input_str);
t_token_type	get_token_type(char *cmd_str, int i);

#endif
