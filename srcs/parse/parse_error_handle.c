#include "minishell.h"

int parse_error(char *err_msg, int err_ret)
{
	ft_putstr_fd(err_msg, 2);
	return (err_ret);
}
