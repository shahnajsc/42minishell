#include "minishell.h"


void	ft_echo(t_env **env, char *str)
{
	int 	i;
	int 	j;
	char 	*key;

	if (!str)
		return ;
	i = 0;
	if (ft_strchr("$", str[i]))
	{
		j = 0;
		while ((*env)[j].key != NULL)
		{
			key = str + 1;
			if (ft_strcmp((*env)[j].key, key) == 0)
			{
				ft_putstr_fd((*env)[j].value, 1);
				ft_putchar_fd('\n', 1);
				return ;
			}
			j++;
		}
	}
	if (str != NULL)
		ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
}

// void 	ft_nl(char *str)
// {
// 	if (!str)
// 		return ;
// 	if (ft_strchr(*str, 'n'))
// 		ft_putstr_fd(str, 1);
// }
//echo $home
//echo /haamda/abc/

//echo -n $abc
//echo -n 