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
	char	*tok_value;
}	t_token;

typedef struct s_cmd
{
	t_token	*token;
	char	*cmd;
	char	**splitted_cmd;
	int		in_fd;
	int		out_fd;
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
int	tokenize_input(t_mshell *mshell, char *input_str);

//..... ERROR .....//
int		syntax_pre_error(t_mshell *mshell, t_syntax_err syn_err, char *err_value);
//int		parse_error(char *err_msg, int err_ret);

//......UTILS......////
int		check_char_is_quote(char  c);
int		count_pipes(char *input_str);
char	**split_input_by_pipes(int cmd_count, char *input_str);

#endif
