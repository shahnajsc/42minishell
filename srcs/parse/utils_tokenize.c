/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:54:46 by shachowd          #+#    #+#             */
/*   Updated: 2025/04/01 21:22:31 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_char_is_redirect(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	count_pipes(char *input_str)
{
	int	count;

	count = 0;
	while (*input_str)
	{
		while (*input_str && check_char_whitespaces(*input_str))
			input_str++;
		if (*input_str && check_char_is_quote(*input_str))
			input_str = skip_quoted_part(input_str);
		else if (*input_str && *input_str == '|')
		{
			count++;
			input_str++;
		}
		else if (*input_str)
			input_str++;
	}
	return (count);
}

t_token_type	get_token_type(char *cmd_str, int i)
{
	if (check_char_is_redirect(cmd_str[i]))
		return (REDIRECT);
	else if (check_char_whitespaces(cmd_str[i]))
		return (EMPTY);
	else
		return (CMD);
}

void	clean_free_str(char *cmd_str)
{
	if (cmd_str)
	{
		free(cmd_str);
		cmd_str = NULL;
	}
}
