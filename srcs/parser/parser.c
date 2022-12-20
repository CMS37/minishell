#include "../../incs/parser.h"
#include "../../incs/structs.h"

/*
lexer 에서 들어온 문자열 토큰화 후 전달 -> 구조체로 리턴받을듯?

구조체 받아서 오류 검사 후 파싱트리?

rule 1. 맨처음 토큰에 해당문자는 올수없음 {"|", "||", ...};
*/

#include <stdio.h>
#include <string.h>
#include <err.h>

void	error(char	*str)
{
	//$? = 258
	printf("minishell: syntax error near unexpected token `%s\'\n", str);
}

void check_unexpected_token(t_list *list)
{
	t_list	*tmp;
	t_token	*token;

	tmp = list;
	token = (t_token *) tmp->content;
	if (token == NULL)
		return ;
	if (is_unexpected_token(token->value))
		error(token->value);
	while (tmp && (ft_strcmp(token->value, "<") == 0 || ft_strcmp(token->value, ">") == 0))
	{
		tmp = tmp->next;
		token = (t_token *)tmp->content;
		if (is_unexpected_token(token->value))
			error(token->value);
	}
}

void	parsing(t_list *list)
{
	if (list == NULL)
		return ;
	check_unexpected_token(list);
	return ;
}

/*
int	main(void)
{
	t_list	*head;
	t_list	*list;
	t_token	*token;
	
	parsing()

	return (1);
}
*/