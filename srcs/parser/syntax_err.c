// #include "../../incs/parser.h"
// #define SYNTAX_ERR 1
// #define QUOTES_ERR 2

// /*
// int	syntax_err(void)
// {
// 	t_token	*token;
// 	t_token	*prev;
// 	t_token *next;
// 	t_list	*tmp;

// 	tmp = g_var->token_list;
// 	prev = NULL;
// 	while (tmp)
// 	{
// 		token = (t_token *) tmp->content;
// 		tmp = tmp->next;
// 		if (tmp == NULL)
// 			next = NULL;
// 		else
// 			next = (t_token *) tmp->content;
// 		if (token->type == T_PIPE && (next->type == T_PIPE || \
// 			prev == NULL || )
// 			(prev == NULL || next == NULL || find_path(prev->value) || \
// 			next->type == T_PIPE))
// 			return (1);
		
// 		if (token->type >= T_REDIRECT && \
// 			(next != NULL && next->type != T_ARGV))
// 			token->type = 1;
		
// 		prev = token;
// 	}
// 	return (0);
// }
// */

// t_bool	check_syntax_err(void)
// {
// 	t_list	*tmp;

// 	tmp = g_var->token_list;
// 	if (!check_quotes(tmp))
// 	{
// 		printf("TESTMESSAGE \"QUOTES_NOT_PAIR\"\n");
// 		g_var->exit_status = 2;
// 		return (TRUE);
// 	}
// 	return (FALSE);
// //	if (!syntax_err())
// //		return (SYNTAX_ERR);
// }