/*
처리한문법
  1.파이프만 있거나 다음입력값이 인자가아닐경우
	-> ("|", "| <", "| ||", "| pwd")등
  2.리다이렉션다음에 입력값이있을떄 
  	인자가아닌 명렁어나 파이프가오면 에러
	-> ("< |", "pwd > a", )근데 이건되나...? 배쉬테스트필요
  3. 그 외 처리할거?

	아직 코드 최적화 및 디버깅x 테스트필

	할거
	디버깅/최적화/ 토큰타입에 값안들어가는거 확인
*/

#include "../../incs/parser.h"
#include "../../incs/lexer.h"
#include "../../incs/structs.h"
#include <stdio.h>
#include <string.h>
#include <err.h>
#include <stdlib.h>

void	parsing(void);
void	del_cmd(void *cmd);

void	parsing(void)
{
	check_unexpected_token();
	ft_lstclear(&g_var->cmd_list, del_cmd);
	create_cmd_list();
	return ;
}

void	del_cmd(void *cmd)
{
	t_list	*t_cmd;

	t_cmd = (t_list *) cmd;
	ft_lstclear(&t_cmd, del_token);
}

void	check_syntax_err(t_list *list)
{
	t_list	*tmp;
	t_token	*token;
	t_token	*prev;
	t_token *next;

	tmp = list;
	prev = NULL;
	while (tmp)
	{
		token = (t_token *) tmp->content;
		tmp = tmp->next;
		next = (t_token *) tmp->content;
		if (token->type == T_PIPE && (prev == NULL || \
			next == NULL || prev->type != T_ARGV || \
			next->type == T_PIPE))
			token->type = 1;
		if (token->type >= T_REDIRECT && \
			(next != NULL && next->type != T_ARGV))
			token->type = 1;
		prev = token;
	}
}

// void	error(char	*str)
// {
//	// TODO: set exit_status: 258
// 	printf("minishell: syntax error near unexpected token `%s\'\n", str);
// }
