#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_mshell t_mshell;

typedef enum e_token_type{
	CMD,
	ARG,
	PIPE,
	REDIRECT_OUT,
	REDIRECT_IN,
	APPEND_OUT,
	HERE_DOC
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

//...... PARSE .....////
void	parse_input(t_mshell *mshell, char *input_str);

//...... TOKEN .....///
void	tokenize_input(t_mshell *mshell, char *input_str);

//..... ERROR .....//
int		parse_error(char *err_msg, int err_ret);

#endif
