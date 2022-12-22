#include "../../incs/execute.h"
#include <unistd.h>

char			**list_to_arr(t_list *cmd);
static size_t	num_of_token(t_list *cmd);

char		**list_to_arr(t_list *cmd)
{
	char	**ret;
	char	**tmp;
	t_token	*token;

	ret = (char **) ft_calloc(sizeof(char *), num_of_token(cmd) + 1, "");
	tmp = ret;
	while (cmd)
	{
		token = (t_token *) cmd->content;
		if (token->type == T_WORD)
			*tmp++ = ft_strdup(token->value);
		else if (token->type == T_REDIRECT)
			cmd = cmd->next;
		cmd = cmd->next;
	}
	return (ret);
}

static size_t	num_of_token(t_list *cmd)
{
	t_token	*token;
	size_t	ret;

	ret = 0;
	while (cmd)
	{
		token = (t_token *) cmd->content;
		if (token->type == T_WORD)
			ret++;
		else if (token->type == T_REDIRECT)
			cmd = cmd->next;
		cmd = cmd->next;
	}
	ft_putendl_fd(ft_itoa(ret), 1);
	return (ret);
}
