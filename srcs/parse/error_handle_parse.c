#include "minishell.h"

void	quote_err_print(char *err_value)
{
	ft_putstr_fd("minishell: unexpected EOF while ", STDERR_FILENO);
	ft_putstr_fd("looking for matching `", STDERR_FILENO);
	ft_putchar_fd(*err_value, STDERR_FILENO);
	ft_putstr_fd("`\n", STDERR_FILENO);
}

void	pipe_err_print(char *err_value)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (*err_value == '|')
		ft_putstr_fd("syntax error near unexpected token '||'\n", STDERR_FILENO);
	else
		ft_putstr_fd("syntax error near unexpected token '|'\n", STDERR_FILENO);
}

void	rd_err_print(char *err_value)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (!*err_value || *err_value == '\n')
		ft_putstr_fd("syntax error near unexpected token 'newline'\n", STDERR_FILENO);
	else if (*err_value == '<' && *(err_value + 1) != '<')
		ft_putstr_fd("syntax error near unexpected token '<'\n", STDERR_FILENO);
	else if (*err_value == '<' && *(err_value + 1) == '<')
		ft_putstr_fd("syntax error near unexpected token '<<'\n", STDERR_FILENO);
	else if (*err_value == '>' && *(err_value + 1) != '>')
		ft_putstr_fd("syntax error near unexpected token '>'\n", STDERR_FILENO);
	else if (*err_value == '>' && *(err_value + 1) == '>')
		ft_putstr_fd("syntax error near unexpected token '>>'\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd("syntax error near unexpected token '", STDERR_FILENO);
		ft_putchar_fd(*err_value, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
}

int	syntax_pre_error(t_mshell *mshell, t_syntax_err syn_err, char *err_value)
{
	if (syn_err == ERR_P)
		pipe_err_print(err_value);
	else if (syn_err == ERR_RD)
		rd_err_print(err_value);
	else if (syn_err == ERR_Q)
		quote_err_print(err_value);
	else if (syn_err == ERR_WHITE_S)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (syn_err == ERR_COMN)
		ft_putstr_fd(err_value, STDERR_FILENO);
	else
	{
		ft_putstr_fd("syntax error near unexpected token '", STDERR_FILENO);
		ft_putchar_fd(*err_value, STDERR_FILENO);
		ft_putstr_fd("`\n", STDERR_FILENO);
	}
	mshell->exit_code = 2;
	return (EXIT_FAILURE);
}

// if >> or >>> error token '>' if more thn >>> error token '>>'
