 #include "../../incs/parser.h"

static t_bool	check_syntax(void);

t_bool	check_syntax_err(void)
{
	if (check_syntax())
	{
		syntax_error();
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	check_syntax(void)
{
	t_token	*token;
	t_token	*next;
	t_list	*tmp;

	tmp = g_var->token_list;
	token = (t_token *) tmp->content;
	if (token && token->type == T_PIPE)
		return (TRUE);
	while (tmp)
	{
		token = (t_token *) tmp->content;
		if (tmp->next != NULL)
			next = (t_token *) tmp->next->content;
		else
			next = NULL;
		if (tmp->next == NULL && token->type == T_PIPE)
			return (TRUE);
		if (token->type == T_REDIRECT && (next == NULL || \
			next->type != T_WORD))
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}
