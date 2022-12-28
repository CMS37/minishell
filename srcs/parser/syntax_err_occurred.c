#include "../../incs/parser.h"

/*
규칙 생각나는대로 추가
1. 리다이랙션 뒤에 인자가 아닌것이 오거나 비어있으면 err
2. 첫문자에 파이프가 오거나 마지막이 파이프로 끝나면 err
3. "", '' err 처리는 토큰화할때 우선처리
*/

t_bool			syntax_err_occurred(void);
static t_bool	print_syntax_err(void);

t_bool	syntax_err_occurred(void)
{
	t_token	*token;
	t_token	*next;
	t_list	*tmp;

	tmp = g_var->token_list;
	token = (t_token *) tmp->content;
	if (token && token->type == T_PIPE)
		return (print_syntax_err());
	while (tmp)
	{
		token = (t_token *) tmp->content;
		if (tmp->next != NULL)
			next = (t_token *) tmp->next->content;
		else
			next = NULL;
		if (token->type == T_PIPE && \
			(tmp->next == NULL || next->type == T_PIPE))
			return (print_syntax_err());
		if (token->type == T_REDIRECT && (next == NULL || \
			next->type != T_WORD))
			return (print_syntax_err());
		tmp = tmp->next;
	}
	return (FALSE);
}

static t_bool	print_syntax_err(void)
{
	g_var->exit_status = 258;
	exit_status("syntax error", NULL, NULL);
	return (TRUE);
}
