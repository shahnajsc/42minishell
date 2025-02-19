#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_mshell t_mshell;

typedef enum e_token_type{
	CMD,
	ARG,
	PIPE,
	RD_IN,
	RD_HEREDOC,
	RD_OUT,
	RD_APPEND,
}  t_token_type;

typedef struct s_token
{
	t_token_type tok_type;
	char	*cmd;
	char	**splited_cmd;
}	t_token;

typedef struct s_tokens_list
{
	t_token	*token;
	size_t	total_token;
}	t_token_list;

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
void	parse_input(t_mshell *mshell, char *input_str);

//...... TOKEN .....///
void	tokenize_input(t_mshell *mshell, char *input_str);

//..... ERROR .....//
int		syntax_pre_error(t_mshell *mshell, t_syntax_err syn_err, char *err_value);
int		parse_error(char *err_msg, int err_ret);

//......UTILS......////
int		check_char_is_quote(char  c);

#endif
