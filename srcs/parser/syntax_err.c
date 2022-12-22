 #include "../../incs/parser.h"
 #define SYNTAX_ERR 1
 #define QUOTES_ERR 2

t_bool	check_syntax_err(void)
{
	t_list	*tmp;

	tmp = g_var->token_list;
	if (!check_quotes(tmp))
	{
		printf("TESTMESSAGE \"QUOTES_NOT_PAIR\"\n");
		g_var->exit_status = 2;
		return (TRUE);
	}
	if (!check_syntax())
	{
		g_var->exit_status = 3;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	check_syntax(void)
{
	t_token	*token;
	t_token	*prev;
	t_token *next;
	t_list	*tmp;

	tmp = g_var->token_list;
	prev = NULL;
	while (tmp)
	{
		token = (t_token *) tmp->content;
		tmp = tmp->next;
		if (tmp == NULL)
			next = NULL;
		else
			next = (t_token *) tmp->content;
		if (token->type == T_PIPE && (next->type == T_PIPE || \
			prev == NULL || next == NULL || prev->type != T_WORD))
			{
				printf("SYNTAX ERR : PIPE\n");
				return (FALSE);
			}
		if (token->type >= T_REDIRECT && \
			(next == NULL || next->type == T_PIPE))
			token->type = 1;
			{
				printf("SYNTAX ERR : NEWLINE\n");
				return (FALSE);
			}
		prev = token;
	}
	return (0);
}
