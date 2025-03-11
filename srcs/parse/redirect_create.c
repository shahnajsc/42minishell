// #include "minishell.h"

// t_redirect_type	get_redirect_type(char *rd_value)
// {
// 	t_redirect_type	type;

// 	type = NONE;
// 	if (ft_strcmp(rd_value, "<") == 0)
// 		type = RD_IN;
// 	else if (ft_strcmp(rd_value, "<<") == 0)
// 		type = RD_HEREDOC;
// 	else if (ft_strcmp(rd_value, ">") == 0)
// 		type = RD_OUT;
// 	else if (ft_strcmp(rd_value, ">>") == 0)
// 		type = RD_APPEND;
// 	return (type);
// }

// int	get_rd_list_len(t_token *token)
// {
// 	t_token	*temp;
// 	int		len;

// 	temp = token;
// 	len = 0;
// 	while (temp)
// 	{
// 		if (temp->tok_type == REDIRECT)
// 			len++;
// 		temp= temp->next;
// 	}
// 	return (len);
// }

// t_redirect	*get_redirect_list(t_token *token, int rd_len)
// {
// 	t_token		*temp;
// 	t_redirect	*rd_list;
// 	t_redirect_type	rd_type;
// 	int			i;

// 	temp = token;
// 	i = 0;
// 	rd_list = ft_calloc(rd_len + 1, sizeof(t_redirect));
// 	if (!rd_list)
// 		return (NULL);
// 	while (temp)
// 	{
// 		if (temp->tok_type == REDIRECT)
// 		{
// 			rd_type = get_redirect_type(temp->tok_value);
// 			rd_list[i].rd_type = rd_type;
// 			rd_list[i].file_deli = ft_strdup(temp->tok_value);
// 			i++;
// 		}
// 		temp = temp->next;
// 	}
// 	return (rd_list);
// }

// t_redirect	*create_redirects_list(t_mshell *mshell, int cmd_id)
// {
// 	t_token		*current_token;
// 	t_redirect	*rd_list;
// 	int			rd_len;

// 	current_token = mshell->cmds[cmd_id].token;
// 	rd_len = get_rd_list_len(current_token);
// 	if (rd_len == 0)
// 		return (NULL);
// 	rd_list = create_redirect_list(current_token, rd_len);
// 	if (!rd_list)
// 		return (NULL);
// 	return (rd_list);
// }
