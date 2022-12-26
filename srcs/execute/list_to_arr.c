#include "../../incs/execute.h"
#include <unistd.h>

char			**list_to_arr(t_list *token_list);
static size_t	num_of_token(t_list *token_list);

char		**list_to_arr(t_list *token_list)
{
	char	**ret;
	char	**tmp;
	t_token	*token;

	ret = (char **) ft_calloc(sizeof(char *), num_of_token(token_list) + 1, "");
	tmp = ret;
	while (token_list)
	{
		token = (t_token *) token_list->content;
		if (token->type == T_WORD)
			*tmp++ = ft_strdup(token->value);
		else if (token->type == T_REDIRECT)
			token_list = token_list->next;
		token_list = token_list->next;
	}
	return (ret);
}

static size_t	num_of_token(t_list *token_list)
{
	t_token	*token;
	size_t	ret;

	ret = 0;
	while (token_list)
	{
		token = (t_token *) token_list->content;
		if (token->type == T_WORD)
			ret++;
		else if (token->type == T_REDIRECT)
			token_list = token_list->next;
		token_list = token_list->next;
	}
	return (ret);
}
