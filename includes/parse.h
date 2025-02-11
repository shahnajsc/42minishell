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


// FUNCTION.......

//.......VALIDATION.....//////
int		input_pre_validation(char *input_str);

//...... PARSE .....////
void	parse_input(t_mshell *mshell, char *input_str);

//...... TOKEN .....///
void	tokenize_input(t_mshell *mshell, char *input_str);

//..... ERROR .....//
int		parse_error(char *err_msg, int err_ret);

#endif
